#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>


class Animation {
public:
  

  SDL_Texture *LoadTexture(std::string filepath, SDL_Renderer *renderTarget) {
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

  void initAnimationPos(int &&xy_init_pos) {       //, int&& wh_init_val
    animationPos.x = animationPos.y = xy_init_pos; // 0
    animationPos.w = frameWidth;
    animationPos.h = frameHeight; // 64*/

    initPos.x = initPos.y = xy_init_pos; // 0
    initPos.w = frameWidth;
    initPos.h = frameHeight;
  }

  void initAnimationRect(int &&sprite_w, int &&sprite_h, int &&x, int &&y) {
    frameWidth = textureWidth / sprite_w;
    frameHeight = textureHeight / sprite_h;

    // Initialize Animation
    animationRect.x = frameWidth * x;  
    animationRect.y = frameHeight * y; 
    animationRect.w = frameWidth;
    animationRect.h = frameHeight;
  }
  
  void resizeAnimation(int &&fwidth, int &&fheight) {
    animationPos.w = fwidth;
    animationPos.h = fheight;
  }

  SDL_Rect &getPlayerPos() { return animationPos; }
  SDL_Rect &getPlayerRect() { return animationRect; }


protected:
  SDL_Rect animationRect;
  SDL_Rect animationPos;
  SDL_Rect initPos;
  float frameWidth, frameHeight;
  int textureWidth, textureHeight;
};