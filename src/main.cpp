#include <algorithm>
#include <ctime>
#include <memory>
#include <vector>

#include "audio.hpp"
#include "camera.hpp"
#include "grid.hpp"
#include "raylib.h"
#include "rlwrap.hpp"
#include "spritesheet.hpp"
#include "things.hpp"

std::vector<std::unique_ptr<Thing>> things;
std::vector<Thing*> spawn_queue;

int main(int argc, char* argv[]) {
    const int screen_width = 800;
    const int screen_height = 600;

    RL::InitWindow(screen_width, screen_height, "Bashar Quest");
    RL::SetTargetFPS(60);

    RL::InitAudioDevice();
    load_sounds();

    auto player = std::make_unique<Player>(14, 14);
    player->max_health = 100;
    player->cur_health = player->max_health;
    things.push_back(std::move(player));

    for (int enemy_count = 20; enemy_count > 0; enemy_count--) {
        const auto x = RL::GetRandomValue(0, GRID_WIDTH - 1);
        const auto y = RL::GetRandomValue(0, GRID_HEIGHT - 1);

        auto enemy = std::make_unique<Enemy>(x, y);
        enemy->max_health = 20;
        enemy->cur_health = enemy->max_health;
        things.push_back(std::move(enemy));
    }

    grid.generate();

    while (!RL::WindowShouldClose()) {
        for (const auto& thing : things) {
            thing->tick();
        }

        grid.tick();

        // TODO: revise when the time comes.
        while (!spawn_queue.empty()) {
            things.push_back(std::unique_ptr<Thing>(spawn_queue.back()));
            spawn_queue.pop_back();
        }

        std::erase_if(things,
                      [](const auto& thing) { return thing->deletion_mark; });

        RL::BeginDrawing();
        RL::BeginMode2D(get_camera());
        {
            RL::ClearBackground({69, 42, 16, 255});

            for (std::size_t i = 0; i < GRID_SIZE; i++) {
                auto& tile = grid.tiles[i];

                const auto x = static_cast<float>(i % GRID_WIDTH);
                const auto y = static_cast<float>(i / GRID_HEIGHT);

                const auto sprite = tile.is_closed() ? Tile::CLOSED : tile.kind;
                draw<Tile>(sprite, {x, y});
            }

            for (const auto& thing : things) {
                const auto& tile_at = grid.tile_at(thing->pos());

                if (tile_at.is_closed()) {
                    continue;
                }

                const auto layers = thing->draw();

                for (const auto& layer : layers) {
                    draw<ThingSprite>(layer, thing->pos());
                }
            }
        }
        RL::EndMode2D();
        RL::EndDrawing();
    }

    RL::CloseAudioDevice();
    RL::CloseWindow();

    return 0;
}
