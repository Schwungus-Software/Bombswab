#include "gamestate.hpp"
#include "camera.hpp"
#include "grid.hpp"
#include "particles.hpp"
#include "raylib.h"
#include "spritesheet.tpp"
#include "things.hpp"
#include <variant>

GSM gsm(new PickLocation);

void GSM::tick() {
    if (stack.empty()) {
        throw Exit("No more game states to process", true);
    }

    const auto trans = stack.back()->tick();

    if (std::holds_alternative<Ignore>(trans)) {
        // Noop.
    } else if (std::holds_alternative<Push>(trans)) {
        const auto push = std::get<Push>(trans);
        stack.push_back(std::unique_ptr<GameState>(push.next));
    } else if (std::holds_alternative<Pop>(trans)) {
        stack.pop_back();
    } else if (std::holds_alternative<Replace>(trans)) {
        const auto replace = std::get<Replace>(trans);
        stack.back().reset(replace.next);
    }
}

static void init_level() {
    const auto pos = mouse_to_grid();

    auto player = std::make_unique<Player>(pos.x, pos.y);
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

    do {
        grid.generate();
    } while (grid.tile_at(pos).kind != Tile::CLOSED);

    grid.open(pos);
}

PickLocation::PickLocation() {
    grid_pos.x = GRID_WIDTH * SPRITE_DIM / 2.0;
    grid_pos.y = GRID_HEIGHT * SPRITE_DIM / 2.0;

    for (std::size_t i = 0; i < GRID_SIZE; i++) {
        auto& tile = grid.tiles[i];
        tile.kind = Tile::CLOSED;
        tile.turns_till_active = 0;
    }
}

GSM::Transition PickLocation::tick() {
    if (IsKeyDown(KEY_A)) {
        grid_pos.x -= SPRITE_DIM;
    }

    if (IsKeyDown(KEY_D)) {
        grid_pos.x += SPRITE_DIM;
    }

    if (IsKeyDown(KEY_W)) {
        grid_pos.y -= SPRITE_DIM;
    }

    if (IsKeyDown(KEY_S)) {
        grid_pos.y += SPRITE_DIM;
    }

    camera_center = grid_pos;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        init_level();
        return GSM::Replace(new Play);
    }

    return GSM::Ignore();
}

GSM::Transition Play::tick() {
    tick_particles();
    tick_things();
    return GSM::Ignore();
}
