#ifndef CHARACTER_H
#define CHARACTER_H

#include "animation.cpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Character : public Animation {
public:
  Character(std::string filepath, SDL_Renderer *renderTarget);
  ~Character();

  enum Dir { kUp, kDown, kLeft, kRight };
  void updateMotion(SDL_Event &ev);
  void automateMotion(int &frameRate, int &switchDir);
  void updateAnimation(Dir);

  SDL_Texture *getCharImage() { return charImage; }

private:
  SDL_Texture *charImage = nullptr;
};

#endif