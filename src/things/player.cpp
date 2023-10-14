#include "actions.hpp"
#include "audio.hpp"
#include "grid.hpp"
#include "rlwrap.hpp"
#include "things.hpp"

void Player::act() {
  const int length = 8;

  if (RL::IsMouseButtonPressed(RL::MOUSE_BUTTON_LEFT)) {
    const auto dir = mouse_to_grid();
    ongoing.reset(new Shoot(new Bullet(dir.x, dir.y)));
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
  // TODO: flip correctly when going up/down too.
  const auto gun = dir == Direction::LEFT ? -Sprite::GUN : Sprite::GUN;
  return {{Sprite::MAN, RL::BLUE}, gun};
}

void Player::step() {
  RL::Sound footstep = {0};

  switch (RL::GetRandomValue(0, 5)) {
  case 0:
    footstep = footstep1;
    break;

  case 1:
    footstep = footstep2;
    break;

  case 2:
    footstep = footstep3;
    break;

  case 3:
    footstep = footstep4;
    break;

  case 4:
    footstep = footstep5;
    break;

  case 5:
    footstep = footstep6;
    break;
  }

  stepped = !stepped;

  if (stepped) {
    play_sound_local(footstep);
  }
}
