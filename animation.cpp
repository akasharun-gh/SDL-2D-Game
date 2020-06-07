#include "animation.h"

SDL_Texture *Animation::LoadTexture(std::string filepath,
                                    SDL_Renderer *renderTarget) {
  SDL_Texture *texture = nullptr;
  SDL_Surface *surface = IMG_Load(filepath.c_str());
  if (surface == NULL)
    std::cout << "Error: " << SDL_GetError() << std::endl;
  else {
    texture = SDL_CreateTextureFromSurface(renderTarget, surface);
    if (texture == NULL) {
      std::cout << "Error: " << SDL_GetError() << std::endl;
    }
  }

  SDL_FreeSurface(surface);

  return texture;
}

void Animation::initAnimationPos(int &&xy_init_pos) { //, int&& wh_init_val
  animationPos.x = animationPos.y = xy_init_pos;      // 0
  animationPos.w = frameWidth;
  animationPos.h = frameHeight; // 64*/

  initPos.x = initPos.y = xy_init_pos; // 0
  initPos.w = frameWidth;
  initPos.h = frameHeight;
}

void Animation::initAnimationRect(int &&sprite_w, int &&sprite_h, int &&x,
                                  int &&y) {
  frameWidth = textureWidth / sprite_w;
  frameHeight = textureHeight / sprite_h;

  // Initialize Animation
  animationRect.x = frameWidth * x;
  animationRect.y = frameHeight * y;
  animationRect.w = frameWidth;
  animationRect.h = frameHeight;
}

void Animation::resizeAnimation(int &&fwidth, int &&fheight) {
  animationPos.w = fwidth;
  animationPos.h = fheight;
}
