include(FetchContent)

function(download_depedencies)
  FetchContent_Declare(
    sdl2webgpu
    GIT_REPOSITORY https://github.com/eliemichel/sdl2webgpu.git
    GIT_TAG 860a0444aff94d82e9cd96ea9085a7e4fefce55d
  )

  FetchContent_MakeAvailable(sdl2webgpu)
endfunction()