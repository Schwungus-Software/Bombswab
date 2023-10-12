#include "actions.hpp"
#include "raylib.h"
#include "rlwrap.hpp"
#include "things.hpp"
#include "audio.hpp"

Player::Player(int x, int y) : Thing(x, y) {
    bool stepped = false;
}

void Player::think() {
  const int length = 5;
  Move* next = nullptr;

  if (RL::IsKeyDown(RL::KEY_LEFT)) {
    next = new Move(Direction::LEFT, length);
  } else if (RL::IsKeyDown(RL::KEY_RIGHT)) {
    next = new Move(Direction::RIGHT, length);
  } else if (RL::IsKeyDown(RL::KEY_UP)) {
    next = new Move(Direction::UP, length);
  } else if (RL::IsKeyDown(RL::KEY_DOWN)) {
    next = new Move(Direction::DOWN, length);
  }

  if (next != nullptr) {
    ongoing.reset(next);
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
