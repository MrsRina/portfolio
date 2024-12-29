#ifndef IO_STATE_HPP
#define IO_STATE_HPP

#include <emscripten.h>
#include <iostream>

#define await(state) while (!state) emscripten_sleep(100)
#define io_log(log) std::cout << log << std::endl; // note: depreciable soon

#include <cinttypes>

namespace io {
  enum results {
    SUCCESS,
    FAILED
  };

  typedef uint64_t result;
}

#endif