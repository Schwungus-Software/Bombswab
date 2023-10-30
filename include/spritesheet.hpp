#pragma once

#include <cstdint>

#include "rlwrap.hpp"

const int SPRITE_DIM = 16;

enum ThingSprite : std::int8_t {
    MAN = 1,
    CORPSE,
    GUN,
    SHOTGUN,
    ROCKET,
    BULLET,
};

enum Tile : std::int8_t {
    CLOSED = 1,
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
};

template <typename SpriteType>
class Spritesheet {
  public:
    const int width, height;
    const char* sheet_path;

    constexpr Spritesheet(const int width, const int height,
                          const char* sheet_path)
        : width(width), height(height), sheet_path(sheet_path) {}

    RL::Texture2D texture() const;
    RL::Texture2D texture_flipped() const;
};

template <typename SpriteType>
struct SpritesheetFor {
    const static Spritesheet<SpriteType> value;
};

template <typename SpriteType>
struct TintedSprite {
    int sprite_idx;
    RL::Color tint;

    TintedSprite() = delete;

    TintedSprite(int idx, RL::Color tint) : sprite_idx(idx), tint(tint) {}
    TintedSprite(int idx) : TintedSprite(idx, RL::WHITE) {}
};

template <typename SpriteType>
void draw(const TintedSprite<SpriteType>&, RL::Vector2);
