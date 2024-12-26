cmake_minimum_required(VERSION 3.31.3)

message(STATUS "Initializing project build")

string(
  REGEX MATCH
  "/emcc"
  compiler_filename
  ${CMAKE_CXX_COMPILER}
)

if (WASM_EMCC_BUILD OR ${compiler_filename} STREQUAL "/emcc")
  message(STATUS "Compiler ID: ${compiler_filename}, WASM build type")
else()
  message(FATAL_ERROR "Could not build application, no WASM CXX was found")
endif()

message(STATUS "Current toolchain: ${CMAKE_CXX_COMPILER_ID}")

if (WIN32)
  # do nothing
elseif(LINUX)
  # do things

  set(
    application_linker_flags
    SDL2 GL GLEW freetype ekg
  )

  set(
    application_emcc_args
    "--bind -s WASM=1 -s USE_SDL=2 -s USE_FREETYPE=1 -s OFFSCREEN_FRAMEBUFFER=1 -s USE_WEBGL2=1"
  )

  set(
    EXECUTABLE_OUTPUT_PATH
    "../build/linux-wasm"
  )
endif()

message(STATUS "Looking for source files...")

file(
  GLOB_RECURSE
  application_source_files
  "./src/*.cpp"
)

project(
  portfolio
  VERSION 1.0.0
)

include_directories(
  src/
  /usr/include/freetype2
)

add_executable(
  portfolio
  ${application_source_files}
)

target_link_libraries(
  portfolio
  ${application_linker_flags}
)

set_target_properties(
  portfolio
  PROPERTIES LINK_FLAGS ${application_emcc_args}
)