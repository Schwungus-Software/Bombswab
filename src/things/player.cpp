#include "actions.hpp"
#include "audio.hpp"
#include "grid.hpp"
#include "rlwrap.hpp"
#include "things.hpp"

void Player::think() {
  const int length = 8;
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
