#include "wolf.h"
#include "animation.h"

// Constructor
Wolf::Wolf(std::string filepath, SDL_Renderer *renderTarget)
    : engine(dev()), random_dir(0, 3) {
  wolfImage = Animation::LoadTexture(filepath, renderTarget);
  SDL_QueryTexture(wolfImage, NULL, NULL, &textureWidth, &textureHeight);
}

// Destructor
Wolf::~Wolf() { SDL_DestroyTexture(wolfImage); }

// Method to automate the motion of the wolf on the screen
void Wolf::automateMotion(int const &frameRate) {

  if (frameRate % 10 == 0) {
    animationRect.x += frameWidth;
    dirSwitchRate += 1;
    if (dirSwitchRate > 1000)
      dirSwitchRate = 0;
    if (dirSwitchRate % 20 == 0)
      dir = static_cast<Dir>(random_dir(engine));

    switch (dir) {
    case Dir::kUp:
      Animation::animationPos.y -= speed;
      animationRect.w = frameWidth / 2;
      animationRect.h = frameHeight * 2;
      animationRect.y = frameHeight * 4;
      animationRect.x += (frameWidth / 2);
      Animation::resizeAnimation(frameWidth / 2, frameHeight * 2);
      if (animationPos.y <= 0)
        animationPos.y = 640 - animationPos.h;
      if (animationRect.x <= (textureWidth - frameWidth * 8.5) ||
          animationRect.x >= (textureWidth - frameWidth * 5.5))
        animationRect.x = frameWidth * 2.5;
      break;

    case Dir::kDown:
      Animation::animationPos.y += speed;
      animationRect.w = frameWidth / 2;
      animationRect.h = frameHeight * 2;
      animationRect.y = frameHeight * 4;
      animationRect.x += (frameWidth / 2);
      Animation::resizeAnimation(frameWidth / 2, frameHeight * 2);
      if (animationPos.y >= (640 - animationPos.h))
        animationPos.y = 0;
      if (animationRect.x >= (textureWidth - frameWidth * 8))
        animationRect.x = 0;
      break;

    case Dir::kLeft:
      Animation::animationPos.x -= speed;
      animationRect.w = frameWidth;
      animationRect.h = frameHeight;
      animationRect.y = frameHeight * 10;
      animationRect.x += frameWidth;
      Animation::resizeAnimation(std::move(frameWidth), std::move(frameHeight));
      if (animationPos.x <= 0)
        animationPos.x = 640 - animationPos.w;
      if (animationRect.x <= (textureWidth / 2) ||
          animationRect.x >= textureWidth)
        animationRect.x = textureWidth / 2;
      break;

    case Dir::kRight:
      Animation::animationPos.x += speed;
      animationRect.w = frameWidth;
      animationRect.h = frameHeight;
      animationRect.y = frameHeight * 4;
      animationRect.x += frameWidth;
      Animation::resizeAnimation(std::move(frameWidth), std::move(frameHeight));
      if (animationPos.x >= (640 - animationPos.h))
        animationPos.x = 0;
      if (animationRect.x <= (textureWidth / 2) ||
          animationRect.x >= textureWidth)
        animationRect.x = textureWidth / 2;
      break;
    }
  }
}

// Method to process animation of wolf after the hero dies
void Wolf::postDeathAnimation(int const &frameRate, Dir d) {
  if (frameRate % 10 == 0) {
    switch (d) {
    case Dir::kUp:
      animationRect.w = frameWidth / 2;
      animationRect.h = frameHeight * 2;
      animationRect.y = frameHeight * 8;
      animationRect.x += (frameWidth / 2);
      Animation::resizeAnimation(frameWidth / 2, frameHeight * 2);
      ;
      if (animationRect.x >= (textureWidth - frameWidth * 7.5))
        animationRect.x = 0;
      break;

    case Dir::kDown:
      animationRect.w = frameWidth / 2;
      animationRect.h = frameHeight * 2;
      animationRect.y = frameHeight * 8;
      animationRect.x += (frameWidth / 2);
      Animation::resizeAnimation(frameWidth / 2, frameHeight * 2);
      if (animationRect.x <= (textureWidth - frameWidth * 7.5) ||
          animationRect.x >= (textureWidth - frameWidth * 5))
        animationRect.x = frameWidth * 2.5;
      break;

    case Dir::kLeft:
      animationRect.w = frameWidth;
      animationRect.h = frameHeight;
      animationRect.y = frameHeight * 5;
      animationRect.x += frameWidth;
      Animation::resizeAnimation(std::move(frameWidth), std::move(frameHeight));
      if (animationRect.x <= (textureWidth / 2) ||
          animationRect.x >= textureWidth)
        animationRect.x = textureWidth / 2;
      break;

    case Dir::kRight:
      animationRect.w = frameWidth;
      animationRect.h = frameHeight;
      animationRect.y = frameHeight * 11;
      animationRect.x += frameWidth;
      Animation::resizeAnimation(std::move(frameWidth), std::move(frameHeight));
      if (animationRect.x <= (textureWidth / 2) ||
          animationRect.x >= textureWidth)
        animationRect.x = textureWidth / 2;
      break;
    }
  }
}
