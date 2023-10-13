#include <cmath>

#include "grid.hpp"
#include "spritesheet.hpp"

RL::Vector2 mouse_to_grid() {
  // TODO: refactor after the camera is added.
  auto mouse = RL::GetMousePosition();
  mouse.x = static_cast<int>(mouse.x / SPRITE_DIM);
  mouse.y = static_cast<int>(mouse.y / SPRITE_DIM);
  return mouse;
}
