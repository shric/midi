cmake_minimum_required(VERSION 3.16)
project(midi)
set(CMAKE_CXX_STANDARD 20)
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

find_package(SDL2 REQUIRED)
find_package(PortMidi REQUIRED)

# Generate gl3w headers and sources
execute_process(
COMMAND cmake .
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/gl3w
)

execute_process(
COMMAND cmake --build .
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/gl3w
)

set(gl3w_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/gl3w/include)

# compile gl3w.c to library
add_library(gl3w ${CMAKE_CURRENT_SOURCE_DIR}/libs/gl3w/src/gl3w.c)

include_directories(
    ${gl3w_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIRS}
    ${PORTMIDI_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/libs/imgui
    ${CMAKE_SOURCE_DIR}/libs/imgui/impl
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_IMPL_OPENGL_LOADER_GL3W -Wall")

add_library (imgui 
    libs/imgui/impl/imgui_impl_sdl.cpp libs/imgui/impl/imgui_impl_opengl3.cpp
    libs/imgui/imgui.cpp libs/imgui/imgui_draw.cpp libs/imgui/imgui_widgets.cpp)

add_executable(midi
               src/main.cpp
               src/Piano.cpp src/Piano.h src/Midi.cpp src/Midi.h src/Audio.cpp src/Audio.h src/Log.cpp src/Log.h src/util.cpp src/util.h)

target_link_libraries(midi ${PORTMIDI_LIBRARIES} ${SDL2_LIBRARIES} imgui gl3w ${CMAKE_DL_LIBS})
