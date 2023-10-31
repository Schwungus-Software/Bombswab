#include <cmath>

#include "grid.hpp"
#include "spritesheet.hpp"
#include "things.hpp"
#include "utils.hpp"

Grid grid;

Grid::Grid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        auto& tile = tiles[i];
        tile.kind = RL::GetRandomValue(1, 10) == 1 ? Tile::MINE : Tile::EMPTY;
        tile.state = TileState::CLOSED;
    }

    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            float fx = x;
            float fy = y;

            if (tile_at({fx, fy}).kind != Tile::EMPTY) {
                continue;
            }

            std::int8_t mines = 0;

            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (tile_at({fx + dx, fy + dy}).kind == Tile::MINE) {
                        mines++;
                    }
                }
            }

            if (mines != 0) {
                const auto ind = static_cast<Tile>(Tile::_1 + mines - 1);
                tiles[x + (y * GRID_WIDTH)].kind = ind;
            }
        }
    }
}

GridTile& Grid::tile_at(RL::Vector2 pos) {
    static GridTile empty{TileState::OPEN, Tile::EMPTY};

    int i = static_cast<int>(pos.x) + (static_cast<int>(pos.y) * GRID_WIDTH);
    return (i < 0 || i >= GRID_SIZE) ? empty : tiles[i];
}

bool Grid::is_open(RL::Vector2 pos) {
    const auto& tile = tile_at(pos);
    return tile.state == TileState::OPEN;
}

void Grid::open(RL::Vector2 pos, bool click_triggered) {
    auto& tile = tile_at(pos);

    if (tile.state == TileState::OPEN) {
        return;
    }

    if (click_triggered && tile.state == TileState::FLAGGED) {
        return;
    }

    tile.state = TileState::OPEN;

    switch (tile.kind) {
        case Tile::EMPTY:
            open({pos.x, pos.y - 1});
            open({pos.x - 1, pos.y - 1});
            open({pos.x - 1, pos.y});
            open({pos.x - 1, pos.y + 1});
            open({pos.x, pos.y + 1});
            open({pos.x + 1, pos.y + 1});
            open({pos.x + 1, pos.y});
            open({pos.x + 1, pos.y - 1});
            break;

        case Tile::MINE:
            for (int xx = -1; xx < 2; xx++) {
                for (int yy = -1; yy < 2; yy++) {
                    for (const auto& thing : things) {
                        if (thing->x == (pos.x + xx) &&
                            thing->y == (pos.y + yy)) {
                            thing->damage(20);
                        }
                    }
                }
            }

            tile.kind = Tile::MINE_HIT;

            {
                const auto boom = pick(explosions);
                play_sound_at(*boom, pos);
            }

            open({pos.x, pos.y - 1});
            open({pos.x - 1, pos.y - 1});
            open({pos.x - 1, pos.y});
            open({pos.x - 1, pos.y + 1});
            open({pos.x, pos.y + 1});
            open({pos.x + 1, pos.y + 1});
            open({pos.x + 1, pos.y});
            open({pos.x + 1, pos.y - 1});
            break;
        default:
            // Don't care about the rest.
            break;
    }
}

RL::Vector2 mouse_to_grid() {
    // TODO: refactor after the camera is added.
    auto mouse = RL::GetMousePosition();
    mouse.x = static_cast<int>(mouse.x / SPRITE_DIM);
    mouse.y = static_cast<int>(mouse.y / SPRITE_DIM);

    return mouse;
}
