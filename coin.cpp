#include <random>
#include "coin.h"
#include "animation.h"

Coin::Coin(std::string filepath, SDL_Renderer *renderTarget)
    : engine(dev()), random_w(10, 608), random_h(10, 608) {
  coinImage = Animation::LoadTexture(filepath, renderTarget);
  SDL_QueryTexture(coinImage, NULL, NULL, &textureWidth, &textureHeight);
}

void Coin::spinAnimation(int const &frameRate) {
  if (frameRate % 10 == 0) {
    animationRect.x += frameWidth;

    if (animationRect.x >= textureWidth)
      animationRect.x = 0;
  }
}

void Coin::PlaceCoin() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    if (true) {
      animationPos.x = x;
      animationPos.y = y;
      return;
    }
  }
}
