#include "game.h"
#include "animation.h"
#include "character.h"
#include "coin.h"
#include "renderer.h"
#include "wolf.h"

#include <fstream>
#include <iostream>
#include <string>

Game::Game(std::size_t grid_width, std::size_t grid_height) {
  init_highscore();
}

/* Load the initial animations of each object associated with the game by
   reading from sprite sheets and setting to render object. */
void Game::Load_Init_Animations(Renderer &renderer) {
  hero = std::make_shared<Character>("game_images/anime_character.png",
                                     renderer.getRenderer());
  // initAnimationRect(w, h, x, y)
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

  // initailize game background
  game_background = Animation::LoadTexture("game_images/grass_bg.jpg",
                                           renderer.getRenderer());

  // Create coin animation
  coin = std::make_shared<Coin>("game_images/coin-sprite.png",
                                renderer.getRenderer());
  coin->initAnimationRect(8, 3, 0, 1);
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

  // Game Loop : Input, Update, Render
  while (isRunning) {
    frame_start = SDL_GetTicks();

    /* Check for events (key presses, mouse clicks, etc.) associated with game
       player*/
    while (SDL_PollEvent(&ev) != 0) {
      if (ev.type == SDL_QUIT)
        isRunning = false;
      else {
        if (alive)
          hero->updateMotion(ev);
      }
    }

    Update();

    // Render the background and objects
    SDL_RenderClear(renderer.getRenderer());
    SDL_RenderCopy(renderer.getRenderer(), game_background, NULL, NULL);
    renderer.Render(hero, wolf, coin);

    if (score >= lvl2score) {
      renderer.Render(wolf2);
    }

    SDL_RenderPresent(renderer.getRenderer());

    if (!alive) {
      msgBoxDelay++;
      if (msgBoxDelay == 200)
        displayMessageBox(isRunning);
    }

    frame_end = SDL_GetTicks();

    /* Keep track of how long each loop through the input/update/render cycle
       takes. */
    frameRate++;

    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, highscore, frameRate);
      frameRate = 0;
      title_timestamp = frame_end;
    }

    if (frameRate >= 1000)
      frameRate = 0;

    /* If the time for this frame is too small (i.e. frame_duration is
       smaller than the target ms_per_frame), delay the loop to
       achieve the correct frame rate. */
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

/* Check for collison of hero with either wolves or coin.
   If collision happens with coin -> increase score.
   If collision happens with wolves -> set alive flag to false and render
   animation associated with game end scenario*/
void Game::Update() {
  if (score < lvl2score) {
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
    if (score >= lvl2score) {
      wolf2->automateMotion(frameRate);
    }

    if (hero->inCharacterLoc(coin->getPlayerPos())) {
      score++;
      coin->PlaceCoin();
      hero->speed += 0.5;
      if (score % 2 == 0) {
        wolf->speed += 1.0;
        wolf2->speed += 1.0;
      }
    }
  }
}

int Game::GetScore() const { return score; }

// initialize highscore by reading stored value from textfile
void Game::init_highscore() {
  std::fstream hscore_file;
  hscore_file.open("highscore.txt", std::ios::out | std::ios::in);

  if (!hscore_file) {
    hscore_file.open("highscore.txt", std::ios::out);
  } else {
    hscore_file >> highscore;
  }
  hscore_file.close();
}

// Updates game highscore if current score exceeds previous high score
void Game::update_highscore() {
  std::ofstream hsFile;
  hsFile.open("highscore.txt", std::ios::out);
  hsFile << score;
  hsFile.close();
}

void Game::Restart() {
  alive = true;
  hero->initAnimationRect(13, 21, 0, 2);
  hero->initAnimationPos(60);
  hero->speed = 4.0;

  wolf->initAnimationPos(360);
  wolf->initAnimationRect(10, 12, 5, 4);
  wolf->speed = 8.0;

  wolf2->initAnimationPos(240);
  wolf2->initAnimationRect(10, 12, 5, 4);
  wolf2->speed = 8.0;

  coin->PlaceCoin();

  if (score > highscore) {
    update_highscore();
    highscore = score;
  }

  score = 0;
  msgBoxDelay = 0;
}

void Game::displayMessageBox(bool &isRunning) {
  const SDL_MessageBoxButtonData buttons[] = {
      {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Quit"},
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Restart"},
  };
  const SDL_MessageBoxColorScheme colorScheme = {
      {/* .colors (.r, .g, .b) */
       /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
       {255, 0, 0},
       /* [SDL_MESSAGEBOX_COLOR_TEXT] */
       {0, 255, 0},
       /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
       {255, 255, 0},
       /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
       {0, 0, 255},
       /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
       {255, 0, 255}}};

  std::string msg;
  if (score <= highscore)
    msg = "Your score: " + std::to_string(score) +
          ", Highscore: " + std::to_string(highscore) + "\n Choose an action ";
  else
    msg = "Congratulations! New Highscore: " + std::to_string(score);

  const SDL_MessageBoxData messageboxdata = {
      SDL_MESSAGEBOX_INFORMATION, /* .flags */
      NULL,                       /* .window */
      "Game Over!",               /* .title */
      msg.c_str(),                /* .message */
      SDL_arraysize(buttons),     /* .numbuttons */
      buttons,                    /* .buttons */
      &colorScheme                /* .colorScheme */
  };

  int buttonid;
  if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
    SDL_Log("error displaying message box");
    return;
  }

  if (buttonid == -1) {
    SDL_Log("no selection");
  } else if (buttonid == 1) {
    isRunning = false;
    if (score > highscore)
      update_highscore();
  } else {
    Restart();
  }
}