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

struct GridTile {
    TileState state;
    Tile kind;
};

class Grid {
  public:
    std::array<GridTile, GRID_WIDTH * GRID_HEIGHT> tiles;

    Grid();

    GridTile& tile_at(RL::Vector2);
    bool is_open(RL::Vector2);

    void open(RL::Vector2, bool = false);
};

extern Grid grid;

RL::Vector2 mouse_to_grid();
