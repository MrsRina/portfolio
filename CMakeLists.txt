cmake_minimum_required(VERSION 3.31.3)

include(stream.cmake)

message(STATUS "Initializing project build")

if (CMAKE_TOOLCHAIN_FILE)
  string(
    REGEX MATCH
    "/Emscripten"
    compiler_filename
    ${CMAKE_TOOLCHAIN_FILE}
  )

  if (WASM_EMCC_BUILD OR ${compiler_filename} STREQUAL "/Emscripten")
    message(STATUS "Compiler ID: ${compiler_filename}, WASM build type")
  else()
    message(FATAL_ERROR "Could not build application, no WASM CXX was found")
  endif()
endif()

message(STATUS "Current toolchain: ${CMAKE_CXX_COMPILER}")

set(
  application_external_dependencies_linker_flags
  ekg
)

set(
  EXECUTABLE_OUTPUT_PATH
  "../"
)

project(
  portfolio
  VERSION 1.0.0
)

add_library(SDL2_SDL2 INTERFACE)
target_link_options(SDL2_SDL2 INTERFACE -sUSE_SDL=2)
add_library(SDL2::SDL2 ALIAS SDL2_SDL2)

add_library(Freetype INTERFACE)
target_link_options(Freetype INTERFACE -sUSE_FREETYPE=1)

add_library(webgpu INTERFACE)
target_link_options(webgpu INTERFACE -sUSE_WEBGPU=1)

add_library(gles3 INTERFACE)
target_link_options(webgpu INTERFACE -sUSE_WEBGL2=1)

#download_depedencies()

message(STATUS "Looking for source files...")

file(
  GLOB_RECURSE
  application_source_files
  "./src/*.cpp"
)

include_directories(
  src
  /usr/include/freetype2
)

message(
  STATUS
  "Direct included `/usr/include/freetype2`"
)

add_executable(
  portfolio
  ${application_source_files}
)

target_link_libraries(
  portfolio
  SDL2::SDL2 Freetype GLEW
  ${application_external_dependencies_linker_flags}
)

set_target_properties(
  portfolio
  PROPERTIES
  LINK_FLAGS "-sWASM=1 -sUSE_WEBGL2=1 -sASYNCIFY=1 --preload-file ../assets --bind"
  CXX_STANDARD 17
)