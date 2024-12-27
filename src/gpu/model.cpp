#include "model.hpp"
#include "application/core.hpp"
#include "requests.hpp"

#include <sdl2webgpu.h>

io::result gpu::model_create_context(
  gpu::context_t *p_context,
  gpu::context_create_info *p_context_create_info
) {
  if (p_context == nullptr || p_context_create_info == nullptr) {
    return io::results::FAILED;
  }

  p_context->p_tag = p_context_create_info->p_tag;

  WGPUInstanceDescriptor instance_desc {
    .nextInChain = nullptr
  };

  p_context->instance = wgpuCreateInstance(&instance_desc);
  p_context->surface = SDL_GetWGPUSurface(p_context->instance, application::p_app->p_sdl_win);

  WGPURequestAdapterOptions req_adapter_options {};
  gpu::request_adapter(
    p_context->instance,
    &p_context->adapter,
    &req_adapter_options
  );

  io_log("adapter meow?")

  return io::results::SUCCESS;
}