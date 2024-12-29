#include "requests.hpp"

io::result gpu::request_adapter(
  WGPUInstance instance,
  WGPUAdapter *p_gpu_adapter,
  WGPURequestAdapterOptions *p_request_adapter_options
) {
  if (p_gpu_adapter == nullptr) {
    return io::results::FAILED;
  }

  struct user_data_t {
  public:
    WGPUAdapter adapter = nullptr;
    bool request_ended {};
    io::result result {};
  };

  user_data_t user_data {};

  auto on_adapter_request_ended {
    [](
      WGPURequestAdapterStatus status,
      WGPUAdapter adapter,
      const char *p_msg,
      void *p_data
    ) {
      user_data_t *p_user_data {
        (user_data_t*) p_data
      };

      if (status == WGPURequestAdapterStatus_Success) {
        p_user_data->adapter = adapter;
        p_user_data->result = io::results::SUCCESS;
      } else {
        p_user_data->result = io::results::FAILED;
        io_log("Failed to create adapter object")
      }

      p_user_data->request_ended = true;
    }
  };

  wgpuInstanceRequestAdapter(
    instance,
    p_request_adapter_options,
    on_adapter_request_ended,
    &user_data
  );

  await(user_data.request_ended);
  *p_gpu_adapter = user_data.adapter;

  return user_data.result;
}