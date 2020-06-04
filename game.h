#ifndef GAME_H
#define GAME_H

#include <random>
#include <SDL2/SDL.h>
#include <memory>
#include "character.cpp"
#include "renderer.h"
#include "coin.cpp"
#include "wolf.cpp"


class Game : Animation {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Renderer &renderer,
           std::size_t target_frame_duration);
  void Load_Init_Animations(Renderer &renderer);
  int GetScore() const;
  bool alive{true};
  int frameRate{0};

 private:
  std::shared_ptr<Character> hero;
  std::shared_ptr<Wolf> wolf;
  std::shared_ptr<Wolf> wolf2;
  std::shared_ptr<Coin> coin;
  SDL_Texture *game_background{nullptr};
  

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int high_score{0};

  void Update();
};

#endif