#include <memory>
#include <vector>

#include "raylib.h"

#include "audio.hpp"
#include "camera.hpp"
#include "grid.hpp"
#include "particles.hpp"
#include "spritesheet.tpp"
#include "things.hpp"

std::vector<std::unique_ptr<Thing>> things;
std::vector<Thing*> spawn_queue;

int main(int argc, char* argv[]) {
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width, screen_height, "Bombswab");
    SetTargetFPS(60);

    InitAudioDevice();
    load_sounds();

    auto player = std::make_unique<Player>(14, 14);
    player->max_health = 100;
    player->cur_health = player->max_health;
    things.push_back(std::move(player));

    for (int enemy_count = 20; enemy_count > 0; enemy_count--) {
        const auto x = GetRandomValue(0, GRID_WIDTH - 1);
        const auto y = GetRandomValue(0, GRID_HEIGHT - 1);

        auto enemy = std::make_unique<Enemy>(x, y);
        enemy->max_health = 20;
        enemy->cur_health = enemy->max_health;
        things.push_back(std::move(enemy));
    }

    grid.generate();

    while (!WindowShouldClose()) {
        PollInputEvents();

        tick_particles();
        tick_things();

        BeginDrawing();
        BeginMode2D(get_camera());
        {
            ClearBackground({69, 42, 16, 255});

            draw_grid();
            draw_things();
            draw_particles();
        }
        EndMode2D();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
