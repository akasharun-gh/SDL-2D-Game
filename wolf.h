#ifndef WOLF_H
#define WOLF_H

#include "animation.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <random>
#include <string>

class Wolf : public Animation {
public:
  Wolf(std::string filepath, SDL_Renderer *renderTarget);
  ~Wolf();

  SDL_Texture *getCharImage() { return wolfImage; }

  Dir dir = Dir::kDown;

  void automateMotion(int const &frameRate);
  void postDeathAnimation(int const &frameRate, Dir d);

  float speed{8.0f};

private:
  SDL_Texture *wolfImage;
  int dirSwitchRate{0};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_dir;
};

#endif