#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "coin.h"
#include "renderer.h"
#include "wolf.h"
#include "animation.h"
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <memory>
#include <random>
#include <string>

// OOP
class Game : Animation {
public:
  Game();
  void Run(Renderer &renderer, std::size_t target_frame_duration);
  // MM
  void Load_Init_Animations(Renderer &renderer);
  int GetScore() const;
  void init_highscore();
  void update_highscore();
  void displayMessageBox(bool &isRunning);
  void Restart();
  std::string getParentDir();

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
  int highscore{0};
  int msgBoxDelay{0};
  
  // score on reaching which the second wolf is introduced to the game
  int lvl2score{5};

  void Update();
};

#endif