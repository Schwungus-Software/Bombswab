#pragma once

#include <array>
#include <vector>

#include "raylib.h"

#include "spritesheets.hpp"

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

    GridTile& tile_at(Vector2);

    void tick();

    void open(Vector2);
    void open_around(Vector2);

    std::vector<Vector2> neighbors_of(Vector2);

    bool is_active(Vector2);
};

extern Grid grid;

void draw_grid();

Vector2 mouse_to_grid();
