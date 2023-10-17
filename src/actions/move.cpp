#include "actions.hpp"

void Move::perform(Thing& actor) {
    // TODO: Add collision detection when the grid is implemented.
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
    actor.step();
}
