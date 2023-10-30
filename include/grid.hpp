#pragma once

#include <array>

#include "rlwrap.hpp"
#include "spritesheet.hpp"

const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 100;
const int GRID_SIZE = GRID_WIDTH * GRID_HEIGHT;

enum class TileState {
    CLOSED = 0,
    DOWN,
    OPEN,
    FLAGGED,
    MAX,
};

class Grid {
  public:
    std::array<Tile, GRID_WIDTH * GRID_HEIGHT> tiles;
    std::array<TileState, GRID_WIDTH * GRID_HEIGHT> tile_states;

    Grid();
    Tile tile_at(RL::Vector2);
    bool tile_open(RL::Vector2);
};

extern Grid grid;

RL::Vector2 mouse_to_grid();
