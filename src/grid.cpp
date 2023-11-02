#include <cmath>
#include <functional>

#include "camera.hpp"
#include "grid.hpp"
#include "particles.hpp"
#include "spritesheet.hpp"
#include "things.hpp"
#include "utils.hpp"

Grid grid;

void draw_grid() {
    for (std::size_t i = 0; i < GRID_SIZE; i++) {
        const auto& tile = grid.tiles[i];

        const auto x = static_cast<float>(i % GRID_WIDTH);
        const auto y = static_cast<float>(i / GRID_HEIGHT);

        const auto sprite = tile.is_closed() ? Tile::CLOSED : tile.kind;
        draw<Tile>(sprite, {x, y});
    }
}

bool GridTile::is_closed() const {
    switch (kind) {
        case Tile::CLOSED:
        case Tile::MINE:
            return true;
        default:
            return false;
    }
}

Grid::Grid() {}

void Grid::generate() {
    for (std::size_t i = 0; i < GRID_SIZE; i++) {
        auto& tile = tiles[i];
        tile.kind = RL::GetRandomValue(1, 5) == 1 ? Tile::MINE : Tile::CLOSED;
        tile.turns_till_active = 0;
    }
}

GridTile& Grid::tile_at(RL::Vector2 pos) {
    static GridTile empty{Tile::CLOSED, 0};

    if (pos.x < 0 || pos.y < 0 || pos.x > GRID_WIDTH || pos.y > GRID_HEIGHT) {
        return empty;
    }

    const auto i = static_cast<std::size_t>(pos.x) + (static_cast<std::size_t>(pos.y) * GRID_WIDTH);

    return (i < 0 || i >= GRID_SIZE) ? empty : tiles[i];
}

std::vector<RL::Vector2> Grid::neighbors_of(RL::Vector2 pos) {
    std::vector<RL::Vector2> result;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx != 0 || dy != 0) {
                result.push_back({pos.x + dx, pos.y + dy});
            }
        }
    }

    return result;
}

void Grid::tick() {
    bool another_iteration;

    for (std::size_t i = 0; i < GRID_SIZE; i++) {
        auto& tile = tiles[i];

        if (tile.turns_till_active > 0) {
            tile.turns_till_active--;
        }
    }

    do {
        another_iteration = false;

        for (std::size_t i = 0; i < GRID_SIZE; i++) {
            auto& tile = tiles[i];

            if (tile.turns_till_active > 0) {
                continue;
            }

            const auto x = static_cast<float>(i % GRID_WIDTH);
            const auto y = static_cast<float>(i / GRID_HEIGHT);

            const RL::Vector2 pos(x, y);

            const auto count_mines = [this, &tile](RL::Vector2 pos) {
                std::size_t mines = 0;

                for (const auto neighbor_pos : neighbors_of(pos)) {
                    auto& neighbor = tile_at(neighbor_pos);

                    if (neighbor.kind == Tile::MINE) {
                        mines++;
                    }
                }

                if (mines == 0) {
                    tile.kind = Tile::EMPTY;
                } else {
                    tile.kind = static_cast<Tile>(Tile::_1 + mines - 1);
                }

                tile.turns_till_active = 0;
            };

            switch (tile.kind) {
                case Tile::EMPTY:
                case Tile::_1:
                case Tile::_2:
                case Tile::_3:
                case Tile::_4:
                case Tile::_5:
                case Tile::_6:
                case Tile::_7:
                case Tile::_8:
                    count_mines(pos);
                    break;
                case Tile::CLOSED: {
                    for (const auto neighbor_pos : neighbors_of(pos)) {
                        auto& neighbor = tile_at(neighbor_pos);

                        if (neighbor.kind == Tile::EMPTY) {
                            count_mines(neighbor_pos);
                            another_iteration = true;
                            break;
                        }
                    }

                    break;
                }
                case Tile::MINE_HIT:
                    spawn_particle(pos, Particle::EXPLOSION, 5);

                    for (int xx = -1; xx <= 1; xx++) {
                        for (int yy = -1; yy <= 1; yy++) {
                            const RL::Vector2 neighbor_pos(pos.x + xx, pos.y + yy);
                            open(neighbor_pos);

                            spawn_particle(neighbor_pos, Particle::EXPLOSION, 20);

                            for (const auto& thing : things) {
                                if (thing->x == neighbor_pos.x && thing->y == neighbor_pos.y) {
                                    thing->damage(20);
                                }
                            }
                        }
                    }

                    {
                        const auto boom = pick(explosions);
                        play_sound_at(*boom, pos);
                    }

                    tile.kind = Tile::EMPTY;
                    another_iteration = true;

                    break;
                default:
                    // Don't care about the rest.
                    break;
            }
        }
    } while (another_iteration);
}

void Grid::open_around(RL::Vector2 pos) {
    open({pos.x, pos.y - 1});
    open({pos.x - 1, pos.y - 1});
    open({pos.x - 1, pos.y});
    open({pos.x - 1, pos.y + 1});
    open({pos.x, pos.y + 1});
    open({pos.x + 1, pos.y + 1});
    open({pos.x + 1, pos.y});
    open({pos.x + 1, pos.y - 1});
}

void Grid::open(RL::Vector2 pos) {
    if (!is_active(pos)) {
        return;
    }

    auto& tile = tile_at(pos);

    switch (tile.kind) {
        case Tile::CLOSED:
            tile.kind = Tile::EMPTY;
            break;
        case Tile::MINE:
            // TODO: play a bomb activation sound (bleep-bleep).
            tile.kind = Tile::MINE_HIT;
            tile.turns_till_active = 30;
            break;
        default:
            // Don't care about the rest.
            break;
    }
}

bool Grid::is_active(RL::Vector2 pos) {
    const auto& tile = tile_at(pos);
    return tile.turns_till_active == 0;
}

RL::Vector2 mouse_to_grid() {
    auto mouse = RL::GetScreenToWorld2D(RL::GetMousePosition(), get_camera());
    mouse.x = static_cast<int>(mouse.x / SPRITE_DIM);
    mouse.y = static_cast<int>(mouse.y / SPRITE_DIM);
    return mouse;
}
