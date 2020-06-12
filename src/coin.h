#ifndef COIN_H
#define COIN_H

#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <random>
#include "animation.h"

// OOP
class Coin : public Animation {
public:
  Coin(std::string filepath, SDL_Renderer *renderTarget);
  ~Coin();

  SDL_Texture *getCharImage() { return coinImage; }

  void PlaceCoin();

  void spinAnimation(int const &frameRate);

private:
  SDL_Texture *coinImage;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
};

#endif