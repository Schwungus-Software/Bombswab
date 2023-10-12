#include "rlwrap.hpp"
#include "spritesheet.hpp"

int main(int argc, char* argv[]) {
  const int screen_width = 800;
  const int screen_height = 600;

  RL::InitWindow(screen_width, screen_height, "Bashar Quest");
  RL::SetTargetFPS(60);

  while (!RL::WindowShouldClose()) {
    RL::BeginDrawing();
    {
      RL::ClearBackground({42, 42, 42, 255});
      draw(Sprite::MAN, {10, 10});
      draw(Sprite::GUN, {11, 10});
      draw(Sprite::CORPSE, {16, 10});
    }
    RL::EndDrawing();
  }

  RL::CloseWindow();

  return 0;
}
