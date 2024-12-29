#include "model.hpp"
#include "requests.hpp"

io::result gpu::model_create_context(
  gpu::context_t *p_context,
  gpu::context_create_info *p_context_create_info
) {
  if (p_context == nullptr || p_context_create_info == nullptr) {
    return io::results::FAILED;
  }

  p_context->p_tag = p_context_create_info->p_tag;
  p_context->instance = wgpuCreateInstance(nullptr);

  if (!p_context->instance) {
    io_log("Failed to create WEBGPU instance object")
    return io::results::FAILED;
  }

  return io::results::SUCCESS;
}