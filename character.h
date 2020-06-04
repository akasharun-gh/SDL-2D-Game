#ifndef CHARACTER_H
#define CHARACTER_H

#include "animation.cpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Character : public Animation {
public:
  //enum class Dir { kUp, kDown, kLeft, kRight };
  Character(std::string filepath, SDL_Renderer *renderTarget);
  ~Character();

  void updateMotion(SDL_Event &ev);
  void deadAnimation();
  void updateAnimation();
  bool inCharacterLoc(SDL_Rect &loc);
  bool alive{true};

  SDL_Texture *getCharImage() { return charImage; }

  Dir dir = Dir::kUp;

  float speed{4.0f};

private:
  SDL_Texture *charImage = nullptr;
};

#endif