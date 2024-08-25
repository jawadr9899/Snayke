#include "include/Snake.hpp"
#include "include/Constants.hpp"
#include "include/Helpers.hpp"
#include <iostream>


bool gameOver = false;

Snake::Snake() : segments(), dir(NoKey), head() {
  this->head = getHead();
  segments.push_back(this->head);
};
sf::RectangleShape Snake::getHead() {
  sf::RectangleShape head(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
  head.setFillColor(SN_HEAD_COLOR);
  head.setPosition(WIDTH / 2.0, HEIGHT / 2.0);
  head.setOutlineColor(sf::Color::White);
  head.setOutlineThickness(1.5);
  return head;
}
void Snake::grow() {
  sf::RectangleShape newSegment(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
  newSegment.setFillColor(SNAKE_COLOR);
  newSegment.setPosition(segments.back().getPosition());
  segments.push_back(newSegment);
}
void Snake::move(float deltaTime) {
  for (int i = segments.size() - 1; i > 0; i--) {
    segments[i].setPosition(segments[i - 1].getPosition());
  }

  if (dir == Direction::UP) {
    segments[0].move(0, -SNAKE_SPEED * deltaTime);
  } else if (dir == Direction::DOWN) {
    segments[0].move(0, SNAKE_SPEED * deltaTime);
  } else if (dir == Direction::LEFT) {
    segments[0].move(-SNAKE_SPEED * deltaTime, 0);
  } else if (dir == Direction::RIGHT) {
    segments[0].move(SNAKE_SPEED * deltaTime, 0);
  } else {
  }
}

void Snake::setDirection(Direction newDir) {
  if (segments.size() > 1) {
    if ((dir == UP && newDir == DOWN) || (dir == DOWN && newDir == UP) ||
        (dir == LEFT && newDir == RIGHT) || (dir == RIGHT && newDir == LEFT))
      return;
  }
  dir = newDir;
}

void Snake::reset() {
  segments.clear();
  segments.push_back(getHead());
}

sf::CircleShape spawnFood(const sf::Text &scoreText) {
  sf::CircleShape food(10);
  food.setFillColor(colors[getRandInt(0, 5)]);
  food.setOutlineColor(sf::Color::White);
  food.setOutlineThickness(1);
  sf::FloatRect scoreBounds = scoreText.getGlobalBounds();
  auto points = getPointsInsideField();
  food.setPosition(points.first, points.second);
  return food;
}

Direction handleMovement() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    return UP;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    return DOWN;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    return LEFT;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    return RIGHT;
  }
  return NoKey;
}
void checkForOutOfBounds(Snake &snake, sf::RenderWindow &window,
                         sf::Text &gameOverText, bool &showGameOver) {

  sf::FloatRect windowBounds(0, 0, WIN_WIDTH, WIN_HEIGHT);

  sf::FloatRect boardBounds((WIN_WIDTH - WIDTH) / 2.0,
                            (WIN_HEIGHT - HEIGHT) / 2.0, WIDTH, HEIGHT);
  sf::FloatRect headBounds = snake.segments[0].getGlobalBounds();

  if (!boardBounds.intersects(headBounds)) {
    std::string file = GAME_OVER_SOUND;
    playSound(file);
    gameOver = showGameOver = true;
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
                       sf::RenderWindow &window, sf::Text &gameOverText,
                       bool &showGameOver) {
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
    gameOver = showGameOver = true;
    window.display();
  }

  if (!gameOver && snake.segments.size() >= 5) {
    auto head = snake.segments[0];
    for (size_t i = 1; i < snake.segments.size(); i++) {
      if (isColliding(head, snake.segments[i])) {
        file = GAME_OVER_SOUND;
        playSound(file);
        gameOver = showGameOver = true;
        break;
      }
    }
  }
}

void init() {
  sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Snyake",
                          sf::Style::Titlebar | sf::Style::Close);

  sf::Image icon;
  if (!icon.loadFromFile(ICON_PATH)) {
    std::cout << "Failed to load icon\n";
    exit(0);
  }

  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  sf::Texture bgTexture;
  if (!bgTexture.loadFromFile(BG_IMG)) {
    exit(0);
  }
  sf::Sprite bgSprite;
  bgSprite.setTexture(bgTexture);

  sf::Font font;
  if (!font.loadFromFile(FONT_NAME))
    exit(0);

  sf::Text txt;
  txt.setFont(font);
  txt.setString("Score: 0");
  txt.setCharacterSize(30);
  txt.setFillColor(SCORE_COLOR);
  txt.setPosition(WIN_WIDTH / 2.0 - txt.getGlobalBounds().width / 2, 10);

  Snake snake;
  sf::CircleShape food = spawnFood(txt);

  sf::Text gameOverText;
  gameOverText.setFont(font);
  gameOverText.setString("Game Over");
  gameOverText.setCharacterSize(60);
  gameOverText.setFillColor(OVER_COLOR);
  gameOverText.setPosition(
      WIN_WIDTH / 2.0 - gameOverText.getGlobalBounds().width / 2,
      WIN_HEIGHT / 2.0 - gameOverText.getGlobalBounds().height / 2);

  sf::Clock clock;
  float snakeMovementInterval = 0.1f;
  float snakeMovementTimer = 0.1f;
  bool showGameOver = false;

  window.setFramerateLimit(FPS);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed)
        window.close();
    }
    if (gameOver && !showGameOver) {
      showGameOver = true;
    }

    if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
      window.clear(BG_COLOR);
      snake.reset();
      food = spawnFood(txt);
      txt.setString("Score: 0");
      gameOver = false;
      showGameOver = false;
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
      checkForOutOfBounds(snake, window, gameOverText, showGameOver);
      checkForCollision(snake, food, txt, window, gameOverText, showGameOver);

      window.clear();
      window.draw(bgSprite);
      for (const auto &segment : snake.segments) {
        window.draw(segment);
      }
      window.draw(food);
      window.draw(txt);

      if (showGameOver) {
        window.draw(gameOverText);
      }

      window.display();
    }
  }
}