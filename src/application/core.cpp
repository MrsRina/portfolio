#include "application/core.hpp"
#include <ekg/os/ekg_opengl.hpp>
#include <ekg/os/ekg_sdl.hpp>
#include <ekg/ekg.hpp>

#include <iostream>
#include <emscripten.h>

application::app_context *application::p_app {};

void application::mainloop() {
  while (SDL_PollEvent(application::p_app->p_sdl_event)) {
    ekg::os::sdl_poll_event(*application::p_app->p_sdl_event);

    if (application::p_app->p_sdl_event->type == SDL_QUIT) {
      return;
    }
  }

  ekg::update();

  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

  ekg::ui::dt = 0.016f;
  ekg::render();

  //SDL_GL_SwapWindow(application::p_app->p_sdl_win);
  SDL_Delay(16);
}

int32_t main() {
  std::cout << "meow" << std::endl;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  application::app_context context {};
  application::p_app = &context;

  application::p_app->p_sdl_win = (
    SDL_CreateWindow(
      "Pompom",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1280,
      720,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
    )
  );

  SDL_Event sdl_event {};
  SDL_GLContext sdl_gl_context {SDL_GL_CreateContext(application::p_app->p_sdl_win)};

  glewInit();

  ekg::runtime_property ekg_runtime_property {
    .p_font_path = "whitneybook.otf",
    .p_font_path_emoji = "twemoji.ttf",
    .p_gpu_api = new ekg::os::opengl("#version 330"),
    .p_os_platform = new ekg::os::sdl(application::p_app->p_sdl_win)
  };

  ekg::init(
    application::p_app->p_ekg_runtime,
    &ekg_runtime_property
  );

  ekg::frame("nemeth e maya", {.x = 10.0f, .y = 10.0f, .w = 200.0f});

  emscripten_set_main_loop(
    application::mainloop,
    -1,
    1
  );

  ekg::quit();
  SDL_Quit();

  return 1;
}