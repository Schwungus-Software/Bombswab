#include <variant>

#include "camera.hpp"
#include "gamestate.hpp"
#include "grid.hpp"
#include "level.hpp"
#include "particles.hpp"
#include "raylib.h"
#include "spritesheet.tpp"
#include "things.hpp"

GSM gsm(new PickLocation);

void GSM::tick() {
    const auto trans = stack.back()->tick();

    if (std::holds_alternative<Ignore>(trans)) {
        // Noop.
    } else if (std::holds_alternative<Push>(trans)) {
        const auto push = std::get<Push>(trans);
        stack.push_back(std::unique_ptr<GameState>(push.next));
    } else if (std::holds_alternative<Pop>(trans)) {
        stack.pop_back();

        if (stack.empty()) {
            throw Exit("No more game states to process", true);
        }
    } else if (std::holds_alternative<Replace>(trans)) {
        const auto replace = std::get<Replace>(trans);
        stack.back().reset(replace.next);
    }

    return;
}

void GSM::overlay() {
    stack.back()->overlay();
}

static void init_level() {
    const auto pos = mouse_to_grid();

    auto player = std::make_unique<Player>(pos.x, pos.y);
    player->max_health = 100;
    player->cur_health = player->max_health;
    level.things.push_back(std::move(player));

    for (int enemy_count = 20; enemy_count > 0; enemy_count--) {
        const auto x = GetRandomValue(0, GRID_WIDTH - 1);
        const auto y = GetRandomValue(0, GRID_HEIGHT - 1);

        auto enemy = std::make_unique<Enemy>(x, y);
        enemy->max_health = 20;
        enemy->cur_health = enemy->max_health;
        level.things.push_back(std::move(enemy));
    }

    do {
        level.grid.generate();
    } while (level.grid.tile_at(pos).kind != Tile::CLOSED);

    level.grid.open(pos);
}

PickLocation::PickLocation() {
    level.things.clear();

    grid_pos.x = GRID_WIDTH * SPRITE_DIM / 2.0;
    grid_pos.y = GRID_HEIGHT * SPRITE_DIM / 2.0;

    for (std::size_t i = 0; i < GRID_SIZE; i++) {
        auto& tile = level.grid.tiles[i];
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

void PickLocation::overlay() {
    const auto color = static_cast<int>(GetTime()) % 2 == 0 ? RED : BLACK;

    const auto text = "Pick a tile to drop off at";
    const int font_size = 30;

    const auto width = MeasureText(text, font_size);
    const auto middle = GetScreenWidth() / 2 - width / 2;

    DrawText(text, middle, 20, font_size, color);
}

GSM::Transition Play::tick() {
    level.tick();

    for (const auto& thing : level.things) {
        if (dynamic_cast<Player*>(thing.get()) != nullptr) {
            return GSM::Ignore();
        }
    }

    return GSM::Replace(new MissionFailed);
}

MissionFailed::MissionFailed() {
    // TODO: play the appropriate theme.
}

GSM::Transition MissionFailed::tick() {
    level.tick();

    delay--;

    if (delay == 0) {
        return GSM::Replace(new PickLocation);
    } else {
        return GSM::Ignore();
    }
}
