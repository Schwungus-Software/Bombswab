#include <cmath>

#include "grid.hpp"
#include "spritesheet.hpp"
#include <things.hpp>

Grid grid;

Grid::Grid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        tiles[i] = RL::GetRandomValue(0, 10) == 0 ? Tile::MINE : Tile::EMPTY;
        tile_states[i] = TileState::CLOSED;
    }

    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            float fx = x;
            float fy = y;

            if (tile_at({fx, fy}) != Tile::EMPTY) {
                continue;
            }

            int mines = 0;

            if (tile_at({fx - 1, fy - 1}) == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx, fy - 1}) == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx + 1, fy - 1}) == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx - 1, fy}) == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx + 1, fy}) == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx - 1, fy + 1}) == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx, fy + 1}) == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx + 1, fy + 1}) == Tile::MINE) {
                ++mines;
            }

            Tile ind;

            switch (mines) {
                case 0:
                    ind = Tile::EMPTY;
                    break;

                case 1:
                    ind = Tile::_1;
                    break;

                case 2:
                    ind = Tile::_2;
                    break;

                case 3:
                    ind = Tile::_3;
                    break;

                case 4:
                    ind = Tile::_4;
                    break;

                case 5:
                    ind = Tile::_5;
                    break;

                case 6:
                    ind = Tile::_6;
                    break;

                case 7:
                    ind = Tile::_7;
                    break;

                case 8:
                    ind = Tile::_8;
                    break;
            }

            tiles[x + (y * GRID_WIDTH)] = ind;
        }
    }
}

Tile Grid::tile_at(RL::Vector2 pos) {
    int i = static_cast<int>(pos.x) + (static_cast<int>(pos.y) * GRID_WIDTH);

    return (i < 0 || i >= GRID_SIZE) ? Tile::EMPTY : tiles[i];
}

bool Grid::tile_open(RL::Vector2 pos) {
    int i = static_cast<int>(pos.x) + (static_cast<int>(pos.y) * GRID_WIDTH);

    if (i < 0 || i >= GRID_SIZE) {
        return false;
    }

    TileState state = tile_states[i];

    if (state == TileState::OPEN || state == TileState::FLAGGED) {
        return false;
    }

    tile_states[i] = TileState::OPEN;

    switch (tiles[i]) {
        case Tile::EMPTY:
            tile_open({pos.x, pos.y - 1});
            tile_open({pos.x - 1, pos.y - 1});
            tile_open({pos.x - 1, pos.y});
            tile_open({pos.x - 1, pos.y + 1});
            tile_open({pos.x, pos.y + 1});
            tile_open({pos.x + 1, pos.y + 1});
            tile_open({pos.x + 1, pos.y});
            tile_open({pos.x + 1, pos.y - 1});
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

            tiles[i] = Tile::MINE_HIT;
            tile_open({pos.x, pos.y - 1});
            tile_open({pos.x - 1, pos.y - 1});
            tile_open({pos.x - 1, pos.y});
            tile_open({pos.x - 1, pos.y + 1});
            tile_open({pos.x, pos.y + 1});
            tile_open({pos.x + 1, pos.y + 1});
            tile_open({pos.x + 1, pos.y});
            tile_open({pos.x + 1, pos.y - 1});
            break;
        default:
            // Don't care about the rest.
            break;
    }

    return true;
}

RL::Vector2 mouse_to_grid() {
    // TODO: refactor after the camera is added.
    auto mouse = RL::GetMousePosition();
    mouse.x = static_cast<int>(mouse.x / SPRITE_DIM);
    mouse.y = static_cast<int>(mouse.y / SPRITE_DIM);

    return mouse;
}
