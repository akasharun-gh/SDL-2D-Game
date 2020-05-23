#ifndef GAME_H
#define GAME_H

#include <random>
#include <SDL2/SDL.h>
#include "character.cpp"
#include "renderer.h"
#include "coin.cpp"


class Game : Animation {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;

 private:
  Character *hero;
  Character *wolf;
  Character *wolf2;
  Coin *coin;
  

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void Update();
};

#endif