#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

using namespace sf;

#define WIDTH 630
#define HEIGHT 630
#define FPS 60
#define SNAKE_SPEED 1000.0f
#define SNAKE_SIZE 15.0f
#define SNAKE_COLOR sf::Color::White
#define SCORE_COLOR sf::Color::White
#define OVER_COLOR sf::Color::Red
#define EAT_SOUND "./lib/sounds/_eat.wav"
#define GAME_OVER_SOUND "./lib/sounds/_over.wav"
#define FONT_NAME "./lib/fonts/Exo.ttf"

enum Direction { UP, DOWN, LEFT, RIGHT, NoKey };
const sf::Color colors[] = {sf::Color::Red,   sf::Color::Cyan,
                            sf::Color::Blue,  sf::Color::Yellow,
                            sf::Color::Green, sf::Color::Magenta};
const sf::Color BG_COLOR(0x17, 0x17, 0x17);
const sf::Color SN_HEAD_COLOR(0x67, 0x67, 0x67);

bool gameOver = false;

struct Snake {
  std::vector<sf::RectangleShape> segments;
  Direction dir = NoKey;

  Snake() { segments.push_back(getHead()); }

  sf::RectangleShape getHead() {
    sf::RectangleShape head(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
    head.setFillColor(SN_HEAD_COLOR);
    head.setPosition(WIDTH / 2.0, HEIGHT / 2.0);
    head.setOutlineColor(sf::Color::White);
    head.setOutlineThickness(1.5);
    return head;
  }

  void grow() {
    sf::RectangleShape newSegment(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
    newSegment.setFillColor(SNAKE_COLOR);
    newSegment.setPosition(segments.back().getPosition());
    segments.push_back(newSegment);
  }

  void move(float deltaTime) {
    for (int i = segments.size() - 1; i > 0; i--) {
      segments[i].setPosition(segments[i - 1].getPosition());
    }

    switch (dir) {
    case UP:
      segments[0].move(0, -SNAKE_SPEED * deltaTime);
      break;
    case DOWN:
      segments[0].move(0, SNAKE_SPEED * deltaTime);
      break;
    case LEFT:
      segments[0].move(-SNAKE_SPEED * deltaTime, 0);
      break;
    case RIGHT:
      segments[0].move(SNAKE_SPEED * deltaTime, 0);
      break;
    case NoKey:
      break;
    }
  }

  void setDirection(Direction newDir) {
    if (segments.size() > 1) {
      if ((dir == UP && newDir == DOWN) || (dir == DOWN && newDir == UP) ||
          (dir == LEFT && newDir == RIGHT) || (dir == RIGHT && newDir == LEFT))
        return;
    }
    dir = newDir;
  }
  void reset() {
    segments.clear();
    segments.push_back(getHead());
  }
};
void playSound(std::string &name) {
  std::thread([name]() {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(name)) {
      std::cerr << "Error: Could not load " << name << std::endl;
      return;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    sf::sleep(buffer.getDuration());
  }).detach();
}

int getRandInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}
sf::CircleShape spawnFood(const sf::Text &scoreText) {
  sf::CircleShape food(10);
  food.setFillColor(colors[getRandInt(0, 5)]);
  food.setOutlineColor(sf::Color::White);
  food.setOutlineThickness(1);
  sf::FloatRect scoreBounds = scoreText.getGlobalBounds();

  float padding = 50.0f;

  float x, y;
  bool validPosition = false;

  while (!validPosition) {
    x = getRandInt(0, WIDTH - 20);
    y = getRandInt(0, HEIGHT - 20);
    sf::FloatRect foodBounds(x, y, food.getRadius() * 2, food.getRadius() * 2);

    if (foodBounds.left + foodBounds.width + padding < scoreBounds.left ||
        foodBounds.left > scoreBounds.left + scoreBounds.width + padding ||
        foodBounds.top + foodBounds.height + padding < scoreBounds.top ||
        foodBounds.top > scoreBounds.top + scoreBounds.height + padding) {
      validPosition = true;
    }
  }

  food.setPosition(x, y);
  return food;
}

Direction handleMovement() {
  if (Keyboard::isKeyPressed(Keyboard::Up)) {
    return UP;
  } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
    return DOWN;
  } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
    return LEFT;
  } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
    return RIGHT;
  }
  return NoKey;
}

void checkForOutOfBounds(Snake &snake, sf::RenderWindow &window,
                         Text &gameOverText) {
  sf::FloatRect windowBounds(0, 0, WIDTH, HEIGHT);
  sf::FloatRect headBounds = snake.segments[0].getGlobalBounds();
  headBounds.left = snake.segments[0].getPosition().x - headBounds.width / 2;
  headBounds.top = snake.segments[0].getPosition().y - headBounds.height / 2;

  if (!gameOver && (headBounds.left < windowBounds.left ||
                    headBounds.top < windowBounds.top ||
                    headBounds.left + headBounds.width >
                        windowBounds.left + windowBounds.width ||
                    headBounds.top + headBounds.height >
                        windowBounds.top + windowBounds.height)) {
    std::string file = GAME_OVER_SOUND;
    playSound(file);
    window.draw(gameOverText);
    gameOver = true;
    window.display();
  }
}

bool isColliding(const sf::RectangleShape &head,
                 const sf::RectangleShape &segment) {
  sf::Vector2f headPos = head.getPosition();
  sf::Vector2f segmentPos = segment.getPosition();
  sf::Vector2f headSize = head.getSize();
  sf::Vector2f segmentSize = segment.getSize();

  return headPos.x < segmentPos.x + segmentSize.x &&
         headPos.x + headSize.x > segmentPos.x &&
         headPos.y < segmentPos.y + segmentSize.y &&
         headPos.y + headSize.y > segmentPos.y;
}
void checkForCollision(Snake &snake, sf::CircleShape &food, sf::Text &txt,
                       sf::RenderWindow &window, sf::Text &gameOverText) {
  std::string file = EAT_SOUND;
  if (snake.segments[0].getGlobalBounds().intersects(food.getGlobalBounds())) {
    snake.grow();
    food = spawnFood(txt);
    playSound(file);
    txt.setString("Score: " + std::to_string(snake.segments.size() - 1));
  }

  if (!gameOver &&
      snake.segments[0].getGlobalBounds().intersects(txt.getGlobalBounds())) {
    file = GAME_OVER_SOUND;
    playSound(file);
    window.draw(gameOverText);
    gameOver = true;
    window.display();
  }

  if (!gameOver && snake.segments.size() >= 5) {
    auto head = snake.segments[0];
    for (size_t i = 1; i < snake.segments.size(); i++) {
      if (isColliding(head, snake.segments[i])) {
        file = GAME_OVER_SOUND;
        playSound(file);
        window.draw(gameOverText);
        gameOver = true;
        window.display();
        break;
      }
    }
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake-For-Class",
                          sf::Style::Titlebar | sf::Style::Close);

  sf::Font font;
  if (!font.loadFromFile(FONT_NAME))
    exit(0);

  sf::Text txt;
  txt.setFont(font);
  txt.setString("Score: 0");
  txt.setCharacterSize(30);
  txt.setFillColor(SCORE_COLOR);
  txt.setPosition(WIDTH / 2.0 - txt.getGlobalBounds().width / 2, 10);

  Snake snake;
  sf::CircleShape food = spawnFood(txt);

  sf::Text gameOverText;
  gameOverText.setFont(font);
  gameOverText.setString("Game Over");
  gameOverText.setCharacterSize(60);
  gameOverText.setFillColor(OVER_COLOR);
  gameOverText.setPosition(
      WIDTH / 2.0 - gameOverText.getGlobalBounds().width / 2,
      HEIGHT / 2.0 - gameOverText.getGlobalBounds().height / 2);

  sf::Clock clock;
  float snakeMovementInterval = 0.1f;
  float snakeMovementTimer = 0.1f;

  window.setFramerateLimit(FPS);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
      window.clear(BG_COLOR);
      snake.reset();
      food = spawnFood(txt);
      txt.setString("Score: 0");
      gameOver = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      window.close();
      exit(0);
    }

    if (!gameOver) {
      Direction m = handleMovement();
      if (m != NoKey) {
        snake.setDirection(m);
      }

      float deltaTime = clock.restart().asSeconds();
      snakeMovementTimer += deltaTime;

      if (snakeMovementTimer >= snakeMovementInterval) {
        snakeMovementTimer = 0.0f;
        snake.move(deltaTime);
      }
      checkForOutOfBounds(snake, window, gameOverText);
      checkForCollision(snake, food, txt, window, gameOverText);

      window.clear(BG_COLOR);
      for (const auto &segment : snake.segments) {
        window.draw(segment);
      }
      window.draw(food);
      window.draw(txt);
    }
    window.display();
  }

  return 0;
}
