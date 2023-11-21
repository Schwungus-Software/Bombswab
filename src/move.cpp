#include "actions.hpp"
#include "level.hpp"

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

    actor.walk_dir = dir;
    actor.action_dir = actor.walk_dir;

    const auto& tile = level.grid.tile_at(actor.pos());

    if (tile.is_closed()) {
        if (!actor.ghost) {
            actor.collide();
        }
    } else {
        actor.step();
    }
}
