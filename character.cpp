#include "character.h"

// Constructor: initailize private members
Character::Character(std::string filepath, SDL_Renderer *renderTarget) {
  charImage = Animation::LoadTexture(filepath, renderTarget);
  SDL_QueryTexture(charImage, NULL, NULL, &textureWidth, &textureHeight);
}

// Destructor
Character::~Character() { SDL_DestroyTexture(charImage); }

// Method to update the motion of the character
void Character::updateMotion(SDL_Event &ev) {
  if (ev.type == SDL_KEYDOWN) {
    switch (ev.key.keysym.sym) {
    case SDLK_UP:
      dir = Dir::kUp;
      break;
    case SDLK_DOWN:
      dir = Dir::kDown;
      break;
    case SDLK_LEFT:
      dir = Dir::kLeft;
      break;
    case SDLK_RIGHT:
      dir = Dir::kRight;
      break;
    }
  }
}

// Method to update charcter animation from sprite sheet
void Character::updateAnimation() {
  switch (dir) {
  case Dir::kUp:
    animationRect.y = frameHeight * 8;
    animationRect.x += frameWidth;
    if (animationPos.y <= 0)
      animationPos.y = 640 - animationPos.h;
    Animation::animationPos.y -= speed;
    if (animationRect.x >= (textureWidth - frameWidth * 4))
      animationRect.x = 0;
    break;

  case Dir::kDown:
    animationRect.y = frameHeight * 10;
    animationRect.x += frameWidth;
    if (animationPos.y >= (640 - animationPos.h))
      animationPos.y = 0;
    Animation::animationPos.y += speed;
    if (animationRect.x >= (textureWidth - frameWidth * 4))
      animationRect.x = 0;
    break;

  case Dir::kLeft:
    animationRect.y = frameHeight * 9;
    animationRect.x += frameWidth;
    if (animationPos.x <= 0)
      animationPos.x = 640 - animationPos.w;
    Animation::animationPos.x -= speed;
    if (animationRect.x >= (textureWidth - frameWidth * 4))
      animationRect.x = 0;
    break;

  case Dir::kRight:
    animationRect.y = frameHeight * 11;
    animationRect.x += frameWidth;
    if (animationPos.x >= (640 - animationPos.w))
      animationPos.x = 0;
    Animation::animationPos.x += speed;
    if (animationRect.x >= (textureWidth - frameWidth * 4))
      animationRect.x = 0;
    break;
  }
}

void Character::deadAnimation(){
    animationRect.y = frameHeight * 20;
    animationRect.x = frameWidth * 5;
    /*if (animationRect.x >= (textureWidth - frameWidth * 6))
      animationRect.x = 0;*/
}

bool Character::inCharacterLoc(SDL_Rect &loc) {
  if (loc.x >= animationPos.x && loc.y >= animationPos.y &&
      loc.x <= (animationPos.x + animationPos.w) &&
      loc.y <= (animationPos.y + animationPos.h))
    return true;
  else
    return false;
}