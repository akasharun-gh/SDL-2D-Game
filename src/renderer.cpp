#include "renderer.h"
#include "character.h"
#include "coin.h"
#include "wolf.h"
#include <iostream>
#include <string>

// OOP
// Constructor
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width), screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create window
  sdl_window = SDL_CreateWindow("Coin Collector", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  renderTarget = SDL_CreateRenderer(
      sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (nullptr == renderTarget) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}
// MM
// Destructor
Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyRenderer(renderTarget);
  SDL_Quit();
}

// Method to update window title 
void Renderer::UpdateWindowTitle(int score, int high_score, int fps) {
  std::string title{"Coin Collector Score: " + std::to_string(score) +
                    " Highscore: " + std::to_string(high_score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
