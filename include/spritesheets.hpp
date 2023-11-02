#pragma once

#include "spritesheet.hpp"

enum ThingSprite : std::int8_t {
    MAN,
    CORPSE,
    RIFLE,
    SHOTGUN,
    ROCKET,
    BULLET,
    PISTOL,
};

enum Tile : std::int8_t {
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
};

enum Particle : std::int8_t {
    EXPLOSION,
};

template <>
inline const Spritesheet<ThingSprite> spritesheet_for<ThingSprite>{7, 1, "assets/spritesheet.png"};

template <>
inline const Spritesheet<Tile> spritesheet_for<Tile>{16, 1, "assets/tilesheet.png"};

template <>
inline const Spritesheet<Particle> spritesheet_for<Particle>{1, 1, "assets/particle_sheet.png"};
