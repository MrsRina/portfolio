include(FetchContent)

function(download_depedencies)
  FetchContent_Declare(
    sdl2webgpu
    GIT_REPOSITORY https://github.com/eliemichel/sdl2webgpu.git
    GIT_TAG main
  )

  FetchContent_MakeAvailable(sdl2webgpu)
endfunction()