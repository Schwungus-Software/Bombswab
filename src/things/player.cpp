#include "actions.hpp"
#include "raylib.h"
#include "rlwrap.hpp"
#include "things.hpp"

Player::Player(int x, int y) : Thing(x, y) {}

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

std::vector<Sprite> Player::draw() { return {Sprite::MAN, Sprite::GUN}; }
