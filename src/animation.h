#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <string>

/* This class has common functionalities that are shared by the character,
   wolf and coin classes. These classes are derived classes of this Animation
   base class. */

class Animation {
public:
  SDL_Texture *LoadTexture(std::string filepath, SDL_Renderer *renderTarget);
  // OOP
  void initAnimationPos(int &&xy_init_pos);
  void initAnimationRect(int &&sprite_w, int &&sprite_h, int &&x, int &&y);
  void resizeAnimation(int &&fwidth, int &&fheight);

  SDL_Rect &getPlayerPos();
  SDL_Rect &getPlayerRect();

protected:
  SDL_Rect animationRect;
  SDL_Rect animationPos;
  SDL_Rect initPos;
  float frameWidth, frameHeight;
  int textureWidth, textureHeight;
  enum class Dir { kUp, kDown, kLeft, kRight };
};

#endif