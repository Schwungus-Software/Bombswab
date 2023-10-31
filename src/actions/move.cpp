#include "actions.hpp"
#include "grid.hpp"

void Move::perform(Thing& actor) {
    switch (dir) {
        case Direction::LEFT:
            actor.x--;
            break;
        case Direction::RIGHT:
            actor.x++;
            break;
        case Direction::UP:
            actor.y--;
            break;
        case Direction::DOWN:
            actor.y++;
            break;
    }

    actor.dir = dir;

    if (grid.tile_at(actor.pos()).kind != Tile::EMPTY) {
        if (!actor.ghost) {
            actor.collide();
        }
    } else {
        actor.step();
    }
}
