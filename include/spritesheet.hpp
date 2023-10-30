#pragma once

#include "rlwrap.hpp"

const int SPRITE_DIM = 16;

// TODO: update every time a new sprite is added until this reaches 16.
const int SPRITESHEET_WIDTH = 6;
const int TILESHEET_WIDTH = 16;

/// Sprite indices inside the spritesheet. Update after changing the PNG.
///
/// Tip: negate to flip horizontally.
enum Sprite {
    MIN = 0,
    MAN,
    CORPSE,
    GUN,
    SHOTGUN,
    ROCKET,
    BULLET,
    MAX,
};

enum class Tile {
    MIN = 0,
    CLOSED,
    FLAG,
    ITEM,
    ITEM_DOWN,
    MINE,
    MINE_HIT,
    NOT_A_MINE,
    EMPTY,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    MAX,
};

struct TintedSprite {
    int sprite_idx;
    RL::Color tint;

    TintedSprite(const int& idx, RL::Color tint)
        : sprite_idx(idx), tint(tint) {}
    TintedSprite(const int& idx) : TintedSprite(idx, RL::WHITE) {}
};

void draw(TintedSprite, RL::Vector2);
void draw_tile(Tile, RL::Vector2);
