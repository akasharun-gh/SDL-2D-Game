#ifndef CHARACTER_H
#define CHARACTER_H

#include "animation.h"
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>

// OOP
class Character : public Animation {
public:
  Character(std::string filepath, SDL_Renderer *renderTarget);
  ~Character();

  void updateMotion(SDL_Event &ev);
  void deadAnimation();
  void updateAnimation();
  bool inCharacterLoc(SDL_Rect &loc);
  bool alive{true};

  SDL_Texture *getCharImage() const; 

  Dir dir = Dir::kUp;

  float speed{3.0f};

private:
  SDL_Texture *charImage = nullptr;
};

#endif