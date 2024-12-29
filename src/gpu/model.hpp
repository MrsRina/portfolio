#ifndef GPU_MODEL_HPP
#define GPU_MODEL_HPP

#include <webgpu/webgpu_cpp.h>
#include "io/state.hpp"

namespace gpu {
  struct context_t {
  public:
    const char *p_tag {};
    WGPUInstance instance {};
    WGPUSurface surface {};
    WGPUAdapter adapter {};
  };

  struct context_create_info {
  public:
    const char *p_tag {};
  };

  io::result model_create_context(
    context_t *p_context,
    context_create_info *p_context_create_info
  );
}

#endif