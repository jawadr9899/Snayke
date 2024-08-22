#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

#define WIDTH 630
#define HEIGHT 630
#define SNAKE_SPEED 1000.0f
#define SNAKE_SIZE 15.0f

using namespace sf;

enum Direction { UP, DOWN, LEFT, RIGHT, NoKey };

struct Snake {
  std::vector<RectangleShape> segments;
  Direction dir = NoKey;
  Snake() {
    RectangleShape head(Vector2f(SNAKE_SIZE, SNAKE_SIZE));
    head.setFillColor(Color::Red);
    head.setOrigin(SNAKE_SIZE / 2, SNAKE_SIZE / 2);
    head.setPosition(WIDTH / 2.0, HEIGHT / 2.0);
    segments.push_back(head);
  }

  void grow() {
    RectangleShape newSegment(Vector2f(SNAKE_SIZE, SNAKE_SIZE));
    newSegment.setFillColor(Color::Green);
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
};

int getRandInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}
CircleShape spawnFood(const Text &scoreText) {
  CircleShape food(10);
  food.setFillColor(Color::Red);


  FloatRect scoreBounds = scoreText.getGlobalBounds();

  float padding = 50.0f;

  float x, y;
  bool validPosition = false;

  while (!validPosition) {
    x = getRandInt(0, WIDTH - 20);
    y = getRandInt(0, HEIGHT - 20);
    FloatRect foodBounds(x, y, food.getRadius() * 2, food.getRadius() * 2);

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

void checkForOutOfBounds(Snake &snake, RenderWindow &window,
                         Text &gameOverText) {
    FloatRect windowBounds(0, 0, WIDTH, HEIGHT);

    FloatRect headBounds = snake.segments[0].getGlobalBounds();
  headBounds.left = snake.segments[0].getPosition().x - headBounds.width / 2;
  headBounds.top = snake.segments[0].getPosition().y - headBounds.height / 2;

    if (headBounds.left < windowBounds.left ||
      headBounds.top < windowBounds.top ||
      headBounds.left + headBounds.width >
          windowBounds.left + windowBounds.width ||
      headBounds.top + headBounds.height >
          windowBounds.top + windowBounds.height) {
    window.draw(gameOverText);
    window.display();
    sf::sleep(sf::seconds(3));
    window.close();
  }
}

void checkForCollision(Snake &snake, CircleShape &food, Text &txt,
                       RenderWindow &window, Text &gameOverText) {
    if (snake.segments[0].getGlobalBounds().intersects(food.getGlobalBounds())) {
    snake.grow();
        food = spawnFood(txt);
    txt.setString("Score: " + std::to_string(snake.segments.size() - 1));
  }

    if (snake.segments[0].getGlobalBounds().intersects(txt.getGlobalBounds())) {
    window.draw(gameOverText);
    window.display();
    sf::sleep(sf::seconds(3));
    window.close();
  }
}

int main() {
  RenderWindow window(VideoMode(WIDTH, HEIGHT), "Snake");

  Font font;
  if (!font.loadFromFile("./Matemasie/Matemasie-Regular.ttf"))
    exit(0);

  Text txt;
  txt.setFont(font);
  txt.setString("Score: 0");
  txt.setCharacterSize(45);
  txt.setFillColor(Color::Green);
  txt.setPosition(WIDTH / 2.0 - txt.getGlobalBounds().width / 2, 0);

  Snake snake;
  CircleShape food = spawnFood(txt);

  Text gameOverText;
  gameOverText.setFont(font);
  gameOverText.setString("Game Over");
  gameOverText.setCharacterSize(60);
  gameOverText.setFillColor(Color::Red);
  gameOverText.setPosition(
      WIDTH / 2.0 - gameOverText.getGlobalBounds().width / 2,
      HEIGHT / 2.0 - gameOverText.getGlobalBounds().height / 2);

  Clock clock;
  float snakeMovementInterval = 0.1f;
  float snakeMovementTimer = 0.0f;

  window.setFramerateLimit(60);

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed)
        window.close();
    }

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

    window.clear();
    for (const auto &segment : snake.segments) {
      window.draw(segment);
    }
    window.draw(food);
    window.draw(txt);
    window.display();
  }

  return 0;
}
