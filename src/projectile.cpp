#include "actions.hpp"
#include "level.hpp"
#include "line.hpp"
#include "spritesheet.tpp"

void Projectile::act() {
    if (--range == 0 || cur_point + 1 == trajectory.size()) {
        const auto collision = intersect_at(true);

        if (collision != nullptr) {
            collision->damage(damage);
        }

        ongoing.reset(new Die);
    } else {
        for (const auto& thing : level.things) {
            if (collides_with(*thing)) {
                thing->damage(damage);

                if (Thing::damage(damage)) {
                    return;
                }
            }
        }

        const auto dest = trajectory[cur_point++];

        Move* next = nullptr;

        if (dest.x > x) {
            next = new Move(Direction::RIGHT, 1);
        } else if (dest.x < x) {
            next = new Move(Direction::LEFT, 1);
        } else if (dest.y > y) {
            next = new Move(Direction::DOWN, 1);
        } else if (dest.y < y) {
            next = new Move(Direction::UP, 1);
        }

        if (next != nullptr) {
            ongoing.reset(next);
        }
    }
}

std::vector<Thing::Sprite> Bullet::draw() {
    return {ThingSprite::BULLET};
}
