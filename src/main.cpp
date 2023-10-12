#include "rlwrap.hpp"

int main(int argc, char* argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 600;

  RL::InitWindow(screenWidth, screenHeight, "Bashar Quest");
  RL::SetTargetFPS(60);

  while (!RL::WindowShouldClose()) {
    RL::BeginDrawing();
    { RL::ClearBackground(RL::BLACK); }
    RL::EndDrawing();
  }

  RL::CloseWindow();

  return 0;
}
