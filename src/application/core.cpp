#include "application/core.hpp"
#include <ekg/os/ekg_sdl.hpp>
#include <ekg/os/ekg_opengl.hpp>
#include <ekg/ekg.hpp>

//#define WEBGPU_BACKEND_DAWN

#include <iostream>
#include <emscripten.h>
//#include <sdl2webgpu.h>

application::app_context *application::p_app {};

void application::mainloop() {
  while (SDL_PollEvent(&application::p_app->sdl_event)) {
    ekg::os::sdl_poll_event(application::p_app->sdl_event);
    if (application::p_app->sdl_event.type == SDL_QUIT) {
      return;
    }
  }

  SDL_DisplayMode sdl_display_mode {};
  SDL_GetDisplayMode(0, 0, &sdl_display_mode);

  if (ekg::ui::width != sdl_display_mode.w || ekg::ui::height != sdl_display_mode.h) {
    ekg::ui::width = sdl_display_mode.w;
    ekg::ui::height = sdl_display_mode.h;

    SDL_SetWindowSize(
      application::p_app->p_sdl_win,
      ekg::ui::width,
      ekg::ui::height
    );
  }

  ekg::update();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.2f, 0.0f, 0.2f, 1.0f);
  glViewport(0.0f, 0.0f, ekg::ui::width, ekg::ui::height);

  ekg::ui::dt = 0.016f;

  ekg::render();

  SDL_GL_SwapWindow(application::p_app->p_sdl_win);
}

int32_t main() {
  std::cout << "meow" << std::endl;

  application::app_context context {};
  application::p_app = &context;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  application::p_app->p_sdl_win = (
    SDL_CreateWindow(
      "Pompom",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      1920,
      1080,
      SDL_WINDOW_OPENGL
    )
  );

  SDL_GLContext sdl_gl_context {SDL_GL_CreateContext(application::p_app->p_sdl_win)};
  glewInit();

  ekg::runtime_property ekg_runtime_property {
    .p_font_path = "assets/comic-mono.ttf",
    .p_font_path_emoji = "assets/twemoji.ttf",
    .p_gpu_api = new ekg::os::opengl("#version 300 es \nprecision highp float;"),
    .p_os_platform = new ekg::os::sdl(application::p_app->p_sdl_win)
  };

  ekg::init(
    &application::p_app->ekg_runtime,
    &ekg_runtime_property
  );

  auto p_calculator_frame = ekg::frame("frame-cat", {.x = 20.0f, .y = 50.0f, .w = 400, .h = 900}, ekg::dock::none)
    ->set_resize(ekg::dock::right | ekg::dock::bottom | ekg::dock::left)
    ->set_drag(ekg::dock::top);

  ekg::button("🐈 oi me pressiona 🤭 mwm 🐮", ekg::dock::fill | ekg::dock::next)
    ->set_text_align(ekg::dock::center)
    ->set_font_size(ekg::font::big)
    ->set_task(
      new ekg::task {
        .info = {
          .tag = "oi bu"
        },
        .function = [](ekg::info &task_info) {
          SDL_Event sdl_event_quit {};
          sdl_event_quit.type = SDL_QUIT;
          SDL_PushEvent(&sdl_event_quit);

          ekg::log() << "task executed: " << task_info.tag;
        }
      },
      ekg::action::activity
    );

  ekg::item themes {};
  themes.push_back(ekg::item("🐮 Theme Schemes"));

  for (auto &[name, theme] : ekg::theme().get_theme_scheme_map()) {
    themes.at(0).emplace_back(name);
  }  

  auto theme_switch_listbox = ekg::listbox("themes", themes, ekg::dock::fill | ekg::dock::next)
    ->set_scaled_height(4);

  ekg::label("Apply theme:", ekg::dock::next)->set_text_align(ekg::dock::left);
  ekg::button("Apply", ekg::dock::fill)
    ->set_task(
      new ekg::task {
        .info = {
          .tag = "apply-theme"
        },
        .function = [theme_switch_listbox](ekg::info&) {
          std::string_view theme_pick {};
          for (ekg::item &items : theme_switch_listbox->p_value->at(0)) {
            if (ekg_bitwise_contains(items.get_attr(), ekg::attr::focused)) {
              ekg::theme().set_current_theme_scheme(items.get_value());
              std::cout << items.get_value() << std::endl;
              break;
            }
          }
        }
      },
      ekg::action::activity
    );
  /*
  gpu::context_create_info context_cinfo {
    .p_tag = "pompom"
  };
  
  gpu::model_create_context(
    &application::p_app->gpu_context,
    &context_cinfo
  );

  application::p_app->gpu_context.surface = SDL_GetWGPUSurface(
    application::p_app->gpu_context.instance,
    application::p_app->p_sdl_win
  );

  WGPURequestAdapterOptions req_adapter_options {
    .nextInChain = nullptr
  };

  gpu::request_adapter(
    application::p_app->gpu_context.instance,
    &application::p_app->gpu_context.adapter,
    &req_adapter_options
  );

  */

  emscripten_set_main_loop(
    application::mainloop,
    -1,
    1
  );

  SDL_Quit();

  return 1;
}