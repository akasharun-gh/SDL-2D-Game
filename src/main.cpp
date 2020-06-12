
//#include "cleanup.h"
#include "game.h"
#include "renderer.h"
#include <iostream>


int main(int argc, char *argv[]) {

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};

  Renderer renderer(kScreenWidth, kScreenHeight);
  Game game;
  game.Run(renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";

  return 0;
}