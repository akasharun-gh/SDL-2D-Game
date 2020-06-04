#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height) {}

void Game::Load_Init_Animations(Renderer &renderer) {
  hero = std::make_shared<Character>("game_images/anime_character.png",
                                     renderer.getRenderer());
  // w, h, x, y
  hero->initAnimationRect(13, 21, 0, 2);
  hero->initAnimationPos(60);

  // Create wolf animation
  wolf = std::make_shared<Wolf>("game_images/wolfsheet6.png",
                                renderer.getRenderer());
  wolf->initAnimationRect(10, 12, 5, 4);
  wolf->initAnimationPos(360);

  wolf2 = std::make_shared<Wolf>("game_images/wolfsheet6.png",
                                 renderer.getRenderer());
  wolf2->initAnimationRect(10, 12, 5, 4);
  wolf2->initAnimationPos(240);

  game_background = Animation::LoadTexture("game_images/grass_bg.jpg",
                                           renderer.getRenderer());
  coin = std::make_shared<Coin>("game_images/coin-sprite.png",
                                renderer.getRenderer());
  coin->initAnimationRect(8, 3, 0, 1);
  coin->initAnimationPos(160);
  coin->resizeAnimation(32, 32);
  coin->PlaceCoin();
}

void Game::Run(Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;

  Load_Init_Animations(renderer);

  bool isRunning = true;

  SDL_Event ev;

  while (isRunning) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    while (SDL_PollEvent(&ev) != 0) {
      if (ev.type == SDL_QUIT)
        isRunning = false;
      else {
        if (alive)
          hero->updateMotion(ev);
      }
    }

    Update();

    SDL_RenderClear(renderer.getRenderer());
    SDL_RenderCopy(renderer.getRenderer(), game_background, NULL, NULL);
    renderer.Render(hero, wolf, coin);

    if (score > 5) {
      // wolf2->automateMotion(frameRate);
      renderer.Render(wolf2);
    }

    SDL_RenderPresent(renderer.getRenderer());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frameRate++;

    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, high_score, frameRate);
      frameRate = 0;
      title_timestamp = frame_end;
    }

    if (frameRate >= 1000)
      frameRate = 0;

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  if (score <= 5) {
    if (hero->inCharacterLoc(wolf->getPlayerPos()) || !alive) {
      alive = false;
      hero->deadAnimation();
      wolf->postDeathAnimation(frameRate, hero->dir);
      coin->spinAnimation(frameRate);
      return;
    }
  } else {
    if (hero->inCharacterLoc(wolf->getPlayerPos()) ||
        hero->inCharacterLoc(wolf2->getPlayerPos()) || !alive) {
      alive = false;
      hero->deadAnimation();
      wolf->postDeathAnimation(frameRate, hero->dir);
      wolf2->postDeathAnimation(frameRate, hero->dir);
      coin->spinAnimation(frameRate);
      return;
    }
  }

  if (alive) {
    hero->updateAnimation();
    wolf->automateMotion(frameRate);
    coin->spinAnimation(frameRate);
    if (score > 5) {
      wolf2->automateMotion(frameRate);
    }

    if (hero->inCharacterLoc(coin->getPlayerPos())) {
      score++;
      coin->PlaceCoin();
      hero->speed += 0.5;
    }
  }
}

int Game::GetScore() const { return score; }