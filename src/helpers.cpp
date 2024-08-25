#include "include/Helpers.hpp"
#include "include/Constants.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <thread>

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
std::pair<float, float> getPointsInsideField() {
  float x = (float)WIDTH / WIN_WIDTH * getRandInt(WIN_WIDTH - WIDTH, WIDTH);
  float y =
      (float)HEIGHT / WIN_HEIGHT * getRandInt(WIN_HEIGHT - HEIGHT, HEIGHT);

  return std::pair<float, float>(x, y);
}