#ifndef APPLICATION_CORE_HPP
#define APPLICATION_CORE_HPP

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <ekg/core/runtime.hpp>

namespace application {
  extern struct app_context {
  public:
    ekg::runtime *p_ekg_runtime {};
    SDL_Window *p_sdl_win {};
    SDL_Event *p_sdl_event {};
  } *p_app;

  void mainloop();
}

#endif