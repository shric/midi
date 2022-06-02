# midi
A C++ program to read MIDI input and display things with [Dear ImGui](https://github.com/ocornut/imgui).

![Screenshot of midi](/doc/screenshots/midi-screenshot.jpg?raw=true)

Currently this is a simple demonstration for me to play with midi input 
(using [portmidi](http://portmedia.sourceforge.net/portmidi/)).

It connects to an input MIDI device and reads events, it shows note up/down events via the keyboard.

## Requirements

- [SDL2](https://www.libsdl.org/)
- [portmidi](http://portmedia.sourceforge.net/portmidi/)

PRs welcome.

## build/run on MacOS

- Fetch submodules: `git submodule update --init`
- Install portmidi: `brew install portmidi`
- Install SDL2: `brew install sdl2`
- Install cmake: `brew install cmake`
```
mkdir build
cd build
cmake ..
make
./midi
```
