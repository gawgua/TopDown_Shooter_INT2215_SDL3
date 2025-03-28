cmake_minimum_required(VERSION 3.10)
project(TopDownShooter)

set(CMAKE_CXX_STANDARD 20)

set(SDLIMAGE_AVIF OFF) # Disable AVIF support because of dav1d
set(SDLIMAGE_WEBP OFF)
set(SDLIMAGE_TIF OFF)
if (CMAKE_HOST_LINUX)
	set(SDLMIXER_MIDI_FLUIDSYNTH OFF) # Disable FluidSynth because of libfluidsynth error on Linux
endif()

# Build deps of SDL from src instead of using system libraries
set(SDLMIXER_VENDORED ON)
set(SDLIMAGE_VENDORED ON)
set(SDLTTF_VENDORED ON)

# Disable shared libraries
set(BUILD_SHARED_LIBS OFF) 
set(SDL_STATIC ON)
set(SDLIMAGE_BUILD_SHARED_LIBS OFF)
set(SDLTTF_BUILD_SHARED_LIBS OFF)
set(SDLMIXER_BUILD_SHARED_LIBS OFF)

# Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_definitions(TOPDOWN_DEBUG)
endif()

add_subdirectory(deps/SDL EXCLUDE_FROM_ALL)
add_subdirectory(deps/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(deps/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(deps/SDL_mixer EXCLUDE_FROM_ALL)

add_subdirectory(src)