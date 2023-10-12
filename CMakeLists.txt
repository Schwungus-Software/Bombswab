cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

add_subdirectory(external/raylib)

project(BasharQuest)

file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(
  BasharQuest
  "src/main.cpp"
  "src/spritesheet.cpp"
  "src/thing.cpp"
  "src/grid.cpp"
  "src/audio.cpp"
  "src/actions/die.cpp"
  "src/actions/move.cpp"
  "src/actions/shoot.cpp"
  "src/things/player.cpp"
  "src/things/bullet.cpp")

set_target_properties(BasharQuest PROPERTIES CXX_STANDARD 23
                                             CXX_STANDARD_REQUIRED ON)

target_include_directories(BasharQuest PRIVATE include "external/raylib/src")

target_link_libraries(BasharQuest raylib)
