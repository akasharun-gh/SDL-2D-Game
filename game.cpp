#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height) {}

void Game::Run(Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  SDL_Texture *game_background = nullptr;
  CoinAnimation *coin = nullptr;

  hero =
      new Character("game_images/anime_character.png", renderer.getRenderer());
  // w, h, x, y
  hero->initAnimationRect(13, 21, 0, 2);
  hero->initAnimationPos(60);

  // Create wolf animation
  wolf = new Character("game_images/wolfsheet6.png", renderer.getRenderer());
  wolf->initAnimationRect(10, 12, 5, 4);
  wolf->initAnimationPos(360);

  game_background = Animation::LoadTexture("game_images/grass_bg.jpg",
                                           renderer.getRenderer());
  coin =
      new CoinAnimation("game_images/coin-sprite.png", renderer.getRenderer());
  coin->initAnimationRect(8, 3, 0, 1);
  coin->initAnimationPos(160);
  coin->resizeAnimation(32, 32);

  int frameRate = 0;
  int frameRate2 = 0;
  bool isRunning = true;
  int switchDir = 0;
  SDL_Event ev;

  while (isRunning) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    while (SDL_PollEvent(&ev) != 0) {
      if (ev.type == SDL_QUIT)
        isRunning = false;
      else {
        hero->updateMotion(ev);
      }
    }

    wolf->automateMotion(frameRate, switchDir);
    coin->spinAnimation(frameRate2);

    SDL_RenderClear(renderer.getRenderer());
    SDL_RenderCopy(renderer.getRenderer(), game_background, NULL, NULL);
    renderer.Render(hero);
    renderer.Render(wolf);
    renderer.Render(coin);
    SDL_RenderPresent(renderer.getRenderer());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frameRate++;
    frameRate2++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frameRate);
      frameRate = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  delete (hero);
  delete (wolf);
}

int Game::GetScore() const { return score; }