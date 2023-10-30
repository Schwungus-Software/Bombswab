#include <cmath>

#include "grid.hpp"
#include "spritesheet.hpp"
#include <things.hpp>

Grid grid;

Grid::Grid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        auto& tile = tiles[i];
        tile.kind = RL::GetRandomValue(0, 10) == 0 ? Tile::MINE : Tile::EMPTY;
        tile.state = TileState::CLOSED;
    }

    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            float fx = x;
            float fy = y;

            if (tile_at({fx, fy}).kind != Tile::EMPTY) {
                continue;
            }

            int mines = 0;

            if (tile_at({fx - 1, fy - 1}).kind == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx, fy - 1}).kind == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx + 1, fy - 1}).kind == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx - 1, fy}).kind == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx + 1, fy}).kind == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx - 1, fy + 1}).kind == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx, fy + 1}).kind == Tile::MINE) {
                ++mines;
            }

            if (tile_at({fx + 1, fy + 1}).kind == Tile::MINE) {
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

            tiles[x + (y * GRID_WIDTH)].kind = ind;
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
                RL::Sound boom = {0};

                switch (RL::GetRandomValue(0, 2)) {
                    case 0:
                        boom = explode1;
                        break;

                    case 1:
                        boom = explode2;
                        break;

                    case 2:
                        boom = explode3;
                        break;
                }

                play_sound_at(boom, pos);
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
