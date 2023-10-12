#include "rlwrap.hpp"
#include "spritesheet.hpp"

int main(int argc, char* argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 600;

  RL::InitWindow(screenWidth, screenHeight, "Bashar Quest");
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
