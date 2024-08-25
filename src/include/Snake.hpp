#pragma once
#include <SFML/Graphics.hpp>

// Snake.hpp
#ifndef SNAKE_CONSTANTS_HPP
#define SNAKE_CONSTANTS_HPP

const sf::Color colors[] = {sf::Color::Red,   sf::Color::Cyan,
                            sf::Color::Blue,  sf::Color::Yellow,
                            sf::Color::Green, sf::Color::Magenta};
const sf::Color BG_COLOR(0x17, 0x17, 0x17);
const sf::Color SN_HEAD_COLOR(0x67, 0x67, 0x67);
enum Direction { UP, DOWN, LEFT, RIGHT, NoKey };

#endif

#ifndef SNAKE_CLASS_HPP
#define SNAKE_CLASS_HPP

class Snake {
public:
  std::vector<sf::RectangleShape> segments;
  Direction dir;
  sf::RectangleShape head;
  Snake();
  sf::RectangleShape getHead();
  void grow();
  void move(float deltaTime);
  void setDirection(Direction newDir);
  void reset();
};
#endif

#ifndef SNAKE_BEHAVIOURS_HPP
#define SNAKE_BEHAVIOURS_HPP

sf::CircleShape spawnFood(const sf::Text &scoreText);
Direction handleMovement();
void checkForOutOfBounds(Snake &snake, sf::RenderWindow &window,
                         sf::Text &gameOverText, bool &showGameOver);
bool isColliding(const sf::RectangleShape &head,
                 const sf::RectangleShape &segment);
void checkForCollision(Snake &snake, sf::CircleShape &food, sf::Text &txt,
                       sf::RenderWindow &window, sf::Text &gameOverText,
                       bool &showGameOver);
void init();

#endif