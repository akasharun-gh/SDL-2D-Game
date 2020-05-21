
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class CoinAnimation : public Animation {
public:
  CoinAnimation(std::string filepath, SDL_Renderer *renderTarget) {
    coinImage = Animation::LoadTexture(filepath, renderTarget);
    SDL_QueryTexture(coinImage, NULL, NULL, &textureWidth, &textureHeight);
  }

  void spinAnimation(int &frameRate) {
    if (frameRate == 10) {
      frameRate = 0;
      animationRect.x += frameWidth;

      if (animationRect.x >= textureWidth)
        animationRect.x = 0;
    }
  }

  SDL_Texture *getCharImage() { return coinImage; }

private:
  SDL_Texture *coinImage;
};