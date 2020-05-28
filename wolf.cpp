#include "wolf.h"

Wolf::Wolf(std::string filepath, SDL_Renderer *renderTarget)
    : engine(dev()), random_dir(0, 3) {
  wolfImage = Animation::LoadTexture(filepath, renderTarget);
  SDL_QueryTexture(wolfImage, NULL, NULL, &textureWidth, &textureHeight);
}

void Wolf::automateMotion(int const &frameRate) {

  if (frameRate % 10 == 0) {
    animationRect.x += frameWidth;
    dirSwitchRate += 1;
    if (dirSwitchRate > 1000)
      dirSwitchRate = 0;
    if (dirSwitchRate % 20 == 0) {
      dir = static_cast<Dir>(random_dir(engine));
    }

    // dir = Dir::kUp;
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

void Wolf::postDeathAnimation(int const &frameRate) {
  // Animation::animationPos.x += speed;
  if (frameRate % 10 == 0) {
    animationRect.w = frameWidth;
    animationRect.h = frameHeight;
    animationRect.y = frameHeight * 5;
    animationRect.x += frameWidth;
    Animation::resizeAnimation(std::move(frameWidth), std::move(frameHeight));
    // if (animationPos.x >= (640 - animationPos.h))
    //  animationPos.x = 0;
    if (animationRect.x <= (textureWidth / 2) ||
        animationRect.x >= textureWidth)
      animationRect.x = textureWidth / 2;
  }
}
