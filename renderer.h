#ifndef RENDERER_H
#define RENDERER_H

#include "character.h"
#include <SDL2/SDL.h>
#include <vector>


class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  // Variadic template class method that handles copying texture to given render target
  template <class T> void Render(std::shared_ptr<T> character);
  template <class T, class... Args> void Render(std::shared_ptr<T> character, Args &&... args);

  void UpdateWindowTitle(int score, int highscore, int fps);
  SDL_Renderer *getRenderer() { return renderTarget; }

private:
  SDL_Window *sdl_window;
  SDL_Renderer *renderTarget;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif