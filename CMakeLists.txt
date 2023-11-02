cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

add_subdirectory(external/raylib)

project(BasharQuest)

file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}")

set(SOURCES
  "src/spritesheet.cpp"
  "src/grid.cpp"
  "src/audio.cpp"
  "src/camera.cpp"
  "src/line.cpp"
  "src/actions.cpp"
  "src/things.cpp"
  "src/item_slot.cpp"
  "src/items.cpp"
  "src/weapons.cpp"
  "src/particles.cpp"
  "src/actions/die.cpp"
  "src/actions/move.cpp"
  "src/actions/shoot.cpp"
  "src/things/humanoid.cpp"
  "src/things/projectile.cpp"
  "src/things/misc.cpp"
  "src/utils.cpp"
  "src/misc.cpp"
  "src/main.cpp")

set(HEADERS
  "include/rlwrap.hpp"
  "include/spritesheet.hpp"
  "include/spritesheets.hpp"
  "include/grid.hpp"
  "include/audio.hpp"
  "include/camera.hpp"
  "include/line.hpp"
  "include/actions.hpp"
  "include/item_slot.hpp"
  "include/items.hpp"
  "include/weapons.hpp"
  "include/particles.hpp"
  "include/actions.hpp"
  "include/things.hpp"
  "include/utils.hpp"
  "include/misc.hpp")

add_executable(BasharQuest ${SOURCES} ${HEADERS})

set_target_properties(BasharQuest PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON)

target_include_directories(BasharQuest PRIVATE include)

target_link_libraries(BasharQuest raylib)
