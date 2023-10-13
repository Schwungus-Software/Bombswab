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
  BULLET,
  MAX,
};

struct TintedSprite {
    Sprite idx;
    RL::Color tint;

    TintedSprite(const Sprite& idx, RL::Color tint) : idx(idx), tint(tint) {}
    TintedSprite(const Sprite& idx) : TintedSprite(idx, RL::WHITE) {}
};

void draw(TintedSprite, RL::Vector2);
