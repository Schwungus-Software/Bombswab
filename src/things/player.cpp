#include "actions.hpp"
#include "grid.hpp"
#include "rlwrap.hpp"
#include "things.hpp"

void Player::think() {
  const int length = 5;
  const int range = 30;

  if (RL::IsMouseButtonDown(RL::MOUSE_BUTTON_LEFT)) {
    const auto dir = mouse_to_grid();
    ongoing.reset(new Shoot(dir.x, dir.y, new Bullet(0, 0, range)));
  } else if (RL::IsKeyDown(RL::KEY_LEFT)) {
    ongoing.reset(new Move(Direction::LEFT, length));
  } else if (RL::IsKeyDown(RL::KEY_RIGHT)) {
    ongoing.reset(new Move(Direction::RIGHT, length));
  } else if (RL::IsKeyDown(RL::KEY_UP)) {
    ongoing.reset(new Move(Direction::UP, length));
  } else if (RL::IsKeyDown(RL::KEY_DOWN)) {
    ongoing.reset(new Move(Direction::DOWN, length));
  }
}

std::vector<TintedSprite> Player::draw() {
  return {{Sprite::MAN, RL::BLUE}, Sprite::GUN};
}
