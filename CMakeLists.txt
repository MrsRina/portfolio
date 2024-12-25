cmake_minimum_required(VERSION 3.31.3)

message(STATUS "Initializing project build")

if (WIN32)
  # do nothing
elseif(LINUX)
  # do things

  set(
    application_linker_flags
    SDL2main SDL2 GL GLEW ekg
  )

  set(
    EXECUTABLE_OUTPUT_PATH
    "../build/linux"
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
)

add_executable(
  portfolio
  ${application_source_files}
)

target_link_libraries(
  portfolio
  ${application_linker_flags}
)