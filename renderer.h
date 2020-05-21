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

  template <class T> void Render(T *character);
  void UpdateWindowTitle(int score, int fps);
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