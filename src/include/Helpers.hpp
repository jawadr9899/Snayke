#pragma once
#include <string>
// Helpers.hpp
#ifndef HELPER_HPP
#define HELPER_HPP
void playSound(std::string &name);
int getRandInt(int min, int max);
std::pair<float, float> getPointsInsideField();
#endif