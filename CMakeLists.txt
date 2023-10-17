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
  "src/line.cpp"
  "src/actions/die.cpp"
  "src/actions/move.cpp"
  "src/actions/shoot.cpp"
  "src/things/player.cpp"
  "src/things/enemy.cpp"
  "src/things/projectile.cpp"
  "src/things/misc.cpp")

set_target_properties(BasharQuest PROPERTIES CXX_STANDARD 20
                                             CXX_STANDARD_REQUIRED ON)

target_include_directories(BasharQuest PRIVATE include)

target_link_libraries(BasharQuest raylib)
