#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "animation.h"
#include "character.h"

// Constructor: initailize private members
Character::Character(std::string filepath, SDL_Renderer *renderTarget) {
  charImage = Animation::LoadTexture(filepath, renderTarget);
  SDL_QueryTexture(charImage, NULL, NULL, &textureWidth, &textureHeight);
}

// MM
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

// Animation for when hero dies
void Character::deadAnimation() {
  animationRect.y = frameHeight * 20;
  animationRect.x = frameWidth * 5;
}

// Method to check for collison
bool Character::inCharacterLoc(SDL_Rect &loc) {
  // Check for collision: if center of referenced Rect is within Rect of the hero
  if (loc.x + (loc.w / 2) >= animationPos.x &&
      loc.y + (loc.h / 2) >= animationPos.y &&
      loc.x + (loc.w / 2) <= (animationPos.x + animationPos.w) &&
      loc.y + (loc.h / 2) <= (animationPos.y + animationPos.h))
    return true;
  else
    return false;

  // Check for collison:Algorithm for bounding box collision
  /*if (animationPos.x + animationPos.w < loc.x ||
      animationPos.x > loc.x + loc.w ||
      animationPos.y + animationPos.h < loc.y || animationPos.y > loc.y + loc.h)
    return false;
  else
    return true;*/
}

// Method to return texture
SDL_Texture *Character::getCharImage() const { return charImage; }