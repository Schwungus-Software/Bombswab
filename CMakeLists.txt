cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(Bombswab CXX)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.0)

set(PROJECT_TARGET ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}")

if(EMSCRIPTEN)
  set(WEB_FLAGS
      "--preload-file assets/ -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WEB_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WEB_FLAGS}")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  file(COPY "${CMAKE_SOURCE_DIR}/index.html" DESTINATION "${CMAKE_BINARY_DIR}")
endif()

set(SOURCES
    "src/grid.cpp"
    "src/audio.cpp"
    "src/gamestate.cpp"
    "src/camera.cpp"
    "src/line.cpp"
    "src/actions.cpp"
    "src/things.cpp"
    "src/level.cpp"
    "src/item_slot.cpp"
    "src/items.cpp"
    "src/weapons.cpp"
    "src/particles.cpp"
    "src/die.cpp"
    "src/move.cpp"
    "src/shoot.cpp"
    "src/humanoid.cpp"
    "src/projectile.cpp"
    "src/keybinds.cpp"
    "src/misc.cpp"
    "src/main.cpp")

set(TEMPLATES "src/utils.tpp" "src/id.tpp" "src/spritesheet.tpp")

set(HEADERS
    "src/grid.hpp"
    "src/audio.hpp"
    "src/gamestate.hpp"
    "src/camera.hpp"
    "src/line.hpp"
    "src/actions.hpp"
    "src/item_slot.hpp"
    "src/items.hpp"
    "src/weapons.hpp"
    "src/particles.hpp"
    "src/things.hpp"
    "src/level.hpp"
    "src/spritesheets.hpp"
    "src/keybinds.hpp"
    "src/misc.hpp")

FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_TARGET} ${SOURCES} ${TEMPLATES} ${HEADERS})
target_link_libraries(${PROJECT_TARGET} raylib)
