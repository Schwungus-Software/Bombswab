#include "spritesheet.hpp"
#include "things.hpp"

void Enemy::act() {
  // TODO: add AI.
}

std::vector<TintedSprite> Enemy::draw() {
  return {{Sprite::MAN, RL::RED}, Sprite::GUN};
}

void Enemy::before_death() {
  auto corpse = std::make_unique<Corpse>(x, y);
  corpse->max_health = max_health;
  corpse->cur_health = std::max(1, max_health / 2);
  spawn_queue.push_back(std::move(corpse));
}
