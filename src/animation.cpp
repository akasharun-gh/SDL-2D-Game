#include <iostream>
#include "animation.h"

// Method to load texture of image to render target  
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

// Method to initialize the position of the animation on the screen
void Animation::initAnimationPos(int &&xy_init_pos) {
  animationPos.x = animationPos.y = xy_init_pos;      
  animationPos.w = frameWidth;
  animationPos.h = frameHeight; 

  initPos.x = initPos.y = xy_init_pos; 
  initPos.w = frameWidth;
  initPos.h = frameHeight;
}

// Method to initialize the sprite animation from the sprite sheet provided
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

// Method to resize the dimensions of the animation on screeen
void Animation::resizeAnimation(int &&fwidth, int &&fheight) {
  animationPos.w = fwidth;
  animationPos.h = fheight;
}

// Returns the current position of the animation
SDL_Rect &Animation::getPlayerPos() { return animationPos; }

// Returns the current Rect of the animation on sprite sheet
SDL_Rect &Animation::getPlayerRect() { return animationRect; }