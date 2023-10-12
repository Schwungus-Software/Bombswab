#pragma once

#include "rlwrap.hpp"

const int SPRITE_DIM = 16;
const int SPRITESHEET_WIDTH = 16;

/// Sprite indices inside the spritesheet. Update after changing the PNG.
enum class Sprite {
  MAN = 0,
  CORPSE,
  GUN,
  SHOTGUN,
  ROCKET,
  MAX,
};

void draw(Sprite, RL::Vector2, RL::Color = RL::WHITE);
