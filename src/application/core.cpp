#include "application/core.hpp"
#include <ekg/os/ekg_sdl.hpp>
#include <ekg/ekg.hpp>

#include <iostream>
#include <emscripten.h>

application::app_context *application::p_app {};

void application::mainloop() {
  while (SDL_PollEvent(&application::p_app->sdl_event)) {
    if (application::p_app->sdl_event.type == SDL_QUIT) {
      return;
    }
  }

  SDL_Delay(16);
}

int32_t main() {
  std::cout << "meow" << std::endl;

  SDL_Init(SDL_INIT_VIDEO);

  application::app_context context {};
  application::p_app = &context;

  application::p_app->p_sdl_win = (
    SDL_CreateWindow(
      "Pompom",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      1280,
      720,
      0
    )
  );

  gpu::context_create_info context_cinfo {
    .p_tag = "pompom"
  };
  
  gpu::model_create_context(
    &application::p_app->gpu_context,
    &context_cinfo
  );

  emscripten_set_main_loop(
    application::mainloop,
    -1,
    1
  );

  SDL_Quit();

  return 1;
}