#include "actions.hpp"
#include "line.hpp"
#include "spritesheet.hpp"
#include "things.hpp"

void Projectile::think() {
  if (--range == 0 || cur_point == trajectory.size()) {
    ongoing.reset(new Die);
  } else {
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

std::vector<TintedSprite> Bullet::draw() {
  // TODO: create a bullet sprite.
  return {Sprite::ROCKET};
}
