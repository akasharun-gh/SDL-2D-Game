#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include <memory>


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

// template class that copies given texture to current rendering target
template <class T> void Renderer::Render(std::shared_ptr<T> character) {
  SDL_RenderCopy(renderTarget, character->getCharImage(),
                 &character->getPlayerRect(), &character->getPlayerPos());
}

// Variadic template to handle rendering of different class types
template <class T, class... Args>
void Renderer::Render(std::shared_ptr<T> character, Args &&... args) {
  Renderer::Render(character);
  Renderer::Render(std::forward<Args>(args)...);
}

#endif