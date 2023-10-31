#pragma once

#include <array>
#include <vector>

#include "rlwrap.hpp"
#include "spritesheet.hpp"

const std::size_t GRID_WIDTH = 32;
const std::size_t GRID_HEIGHT = 32;

const auto GRID_SIZE = GRID_WIDTH * GRID_HEIGHT;

struct GridTile {
    Tile kind;

    /// How long until another state transition may occur.
    std::size_t turns_till_active;

    bool is_closed() const;
};

class Grid {
  public:
    std::array<GridTile, GRID_WIDTH * GRID_HEIGHT> tiles;

    Grid();

    void generate();

    GridTile& tile_at(RL::Vector2);

    void tick();

    void open(RL::Vector2);
    void open_around(RL::Vector2);

    std::vector<RL::Vector2> neighbors_of(RL::Vector2);

    bool is_active(RL::Vector2);
};

extern Grid grid;

RL::Vector2 mouse_to_grid();
