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
      Animation::animationPos.y -= 8;
      Character::updateAnimation(kUp);
      if (animationPos.y <= 0)
        animationPos.y = 480 - animationPos.h;
      break;
    case SDLK_DOWN:
      animationPos.y += 8;
      Character::updateAnimation(kDown);
      if (animationPos.y >= (480 - animationPos.h))
        animationPos.y = 0;
      break;
    case SDLK_LEFT:
      animationPos.x -= 8;
      Character::updateAnimation(kLeft);
      if (animationPos.x <= 0)
        animationPos.x = 640 - animationPos.w;
      break;
    case SDLK_RIGHT:
      animationPos.x += 8;
      Character::updateAnimation(kRight);
      if (animationPos.x >= (640 - animationPos.h))
        animationPos.x = 0;
      break;
    }
  }
}

// Method to update charcter animation from sprite sheet
void Character::updateAnimation(Dir dir) {
  switch (dir) {
  case kUp:
    animationRect.y = frameHeight * 8;
    animationRect.x += frameWidth;
    if (animationRect.x >= (textureWidth - frameWidth * 4))
      animationRect.x = 0;
    break;
  case kDown:
    animationRect.y = frameHeight * 10;
    animationRect.x += frameWidth;
    if (animationRect.x >= (textureWidth - frameWidth * 4))
      animationRect.x = 0;
    break;
  case kLeft:
    animationRect.y = frameHeight * 9;
    animationRect.x += frameWidth;
    if (animationRect.x >= (textureWidth - frameWidth * 4))
      animationRect.x = 0;
    break;
  case kRight:
    animationRect.y = frameHeight * 11;
    animationRect.x += frameWidth;
    if (animationRect.x >= (textureWidth - frameWidth * 4))
      animationRect.x = 0;
    break;
  }
}

void Character::automateMotion(int &frameRate, int &switchDir) {

  if (frameRate == 10) {
    frameRate = 0;
    animationRect.x += frameWidth;

    if (animationRect.x >= textureWidth)
      animationRect.x = textureWidth / 2;

    if (switchDir == 0) {
      animationPos.x += 8;
      if (animationPos.x >= 480) {
        animationRect.y = frameHeight * 10;
        animationPos.x -= 8;
        switchDir = 1;
      }
    } else {
      animationPos.x -= 8;
      if (animationPos.x <= 360) {
        animationRect.y = frameHeight * 4;
        animationPos.x += 8;
        switchDir = 0;
      }
    }
  }
}