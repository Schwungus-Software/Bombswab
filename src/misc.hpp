#pragma once

const int FRAMERATE = 60;
const float TIMESTEP = 1.0 / FRAMERATE;

enum class Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

enum class HandSlot {
    LEFT,
    RIGHT,
};

enum class SpriteFlip {
    DEG_0,
    NEG_0,
    DEG_90,
    NEG_90,
    DEG_180,
    NEG_180,
    DEG_270,
    NEG_270,
};

SpriteFlip flip(const SpriteFlip&);
