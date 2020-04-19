cmake_minimum_required(VERSION 3.16)
project(midi)
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED)
include_directories(. .. libs/gl3w libs/imgui libs/imgui/impl /usr/local/include)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_IMPL_OPENGL_LOADER_GL3W -Wall")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa")

add_executable(midi
               src/main.cpp
               src/Piano.cpp src/Piano.h src/Midi.cpp src/Midi.h src/Audio.cpp src/Audio.h src/Log.cpp src/Log.h src/util.cpp src/util.h
               libs/imgui/impl/imgui_impl_sdl.cpp libs/imgui/impl/imgui_impl_opengl3.cpp
               libs/imgui/imgui.cpp libs/imgui/imgui_draw.cpp libs/imgui/imgui_widgets.cpp
               libs/gl3w/GL/gl3w.c)

target_link_libraries(midi /usr/local/lib/libportmidi.dylib ${SDL2_LIBRARIES})
