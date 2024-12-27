#ifndef GPU_REQUESTS_HPP
#define GPU_REQUESTS_HPP

#include <webgpu/webgpu.h>
#include "io/state.hpp"

namespace gpu {
  io::result request_adapter(
    WGPUInstance instance,
    WGPUAdapter *p_gpu_adapter,
    WGPURequestAdapterOptions *p_request_adapter_options
  );
}

#endif