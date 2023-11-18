cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

add_subdirectory(external/raylib)

project(Bombswab CXX)

set(CMAKE_CXX_STANDARD 20
    CMAKE_CXX_STANDARD_REQUIRED ON)

file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}")

if(EMSCRIPTEN)
  set(WEB_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/assets@assets/ -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WEB_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WEB_FLAGS}")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

set(SOURCES
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
  "src/die.cpp"
  "src/move.cpp"
  "src/shoot.cpp"
  "src/humanoid.cpp"
  "src/projectile.cpp"
  "src/corpse.cpp"
  "src/misc.cpp"
  "src/main.cpp")

set(TEMPLATES
  "src/utils.tpp"
  "src/spritesheet.tpp")

set(HEADERS
  "src/grid.hpp"
  "src/audio.hpp"
  "src/camera.hpp"
  "src/line.hpp"
  "src/actions.hpp"
  "src/item_slot.hpp"
  "src/items.hpp"
  "src/weapons.hpp"
  "src/particles.hpp"
  "src/things.hpp"
  "src/spritesheets.hpp"
  "src/misc.hpp")

add_executable(Bombswab ${SOURCES} ${TEMPLATES} ${HEADERS})
target_link_libraries(Bombswab raylib)
