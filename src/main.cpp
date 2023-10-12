#include <memory>
#include <vector>

#include "rlwrap.hpp"
#include "spritesheet.hpp"
#include "thing.hpp"
#include "things.hpp"

int main(int argc, char* argv[]) {
  const int screen_width = 800;
  const int screen_height = 600;

  RL::InitWindow(screen_width, screen_height, "Bashar Quest");
  RL::SetTargetFPS(60);

  std::vector<std::unique_ptr<Thing>> things;
  things.push_back(std::make_unique<Player>(10, 10));

  while (!RL::WindowShouldClose()) {
    RL::BeginDrawing();
    {
      RL::ClearBackground({69, 42, 16, 255});

      for (const auto& thing : things) {
        thing->tick();

        const auto layers = thing->draw();

        for (const auto& layer : layers) {
          const auto x = static_cast<float>(thing->x);
          const auto y = static_cast<float>(thing->y);
          draw(layer, {x, y});
        }
      }
    }
    RL::EndDrawing();
  }

  RL::CloseWindow();

  return 0;
}
