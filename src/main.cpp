#include <algorithm>
#include <memory>
#include <vector>

#include "audio.hpp"
#include "rlwrap.hpp"
#include "spritesheet.hpp"
#include "thing.hpp"
#include "things.hpp"

std::vector<std::unique_ptr<Thing>> things;
std::vector<std::unique_ptr<Thing>> spawn_queue;

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

    for (int enemy_count = 10; enemy_count > 0; enemy_count--) {
        const auto x = RL::GetRandomValue(0, 29);
        const auto y = RL::GetRandomValue(0, 29);

        auto enemy = std::make_unique<Enemy>(x, y);
        enemy->max_health = 20;
        enemy->cur_health = enemy->max_health;
        things.push_back(std::move(enemy));
    }

    while (!RL::WindowShouldClose()) {
        RL::BeginDrawing();
        {
            RL::ClearBackground({69, 42, 16, 255});

            draw_tile(Tile::ITEM, {0, 0});
            draw_tile(Tile::ITEM, {0, 2});
            draw_tile(Tile::CLOSED, {1, 1});
            draw_tile(Tile::CLOSED, {2, 1});
            draw_tile(Tile::CLOSED, {3, 1});
            draw_tile(Tile::MINE_HIT, {4, 1});

            for (const auto& thing : things) {
                thing->tick();

                const auto layers = thing->draw();

                for (const auto& layer : layers) {
                    const auto x = static_cast<float>(thing->x);
                    const auto y = static_cast<float>(thing->y);
                    draw(layer, {x, y});
                }
            }

            // TODO: revise when the time comes.
            while (!spawn_queue.empty()) {
                things.push_back(std::move(spawn_queue.back()));
                spawn_queue.pop_back();
            }

            std::erase_if(
                things, [](const auto& thing) { return thing->deletion_mark; });
        }
        RL::EndDrawing();
    }

    RL::CloseAudioDevice();
    RL::CloseWindow();

    return 0;
}
