#include "actions.hpp"
#include "spritesheet.hpp"
#include "things.hpp"

void Bullet::think() {
  // TODO: make this bitch move.
  if (--range == 0) {
    ongoing.reset(new Die);
  }
}

std::vector<TintedSprite> Bullet::draw() {
  // TODO: create a bullet sprite.
  return {Sprite::ROCKET};
}
