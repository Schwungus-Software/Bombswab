#pragma once

#include <cmath>
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

    constexpr Spritesheet() : Spritesheet(0, 0, nullptr) {}

    constexpr Spritesheet(const int width, const int height, const char* sheet_path)
        : width(width), height(height), sheet_path(sheet_path) {}

    RL::Texture2D texture() const {
        static const auto texture = RL::LoadTexture(sheet_path);
        return texture;
    }

    RL::Texture2D texture_flipped() const {
        const auto load_texture_flipped = [](RL::Texture2D texture) {
            auto img = RL::LoadImageFromTexture(texture);
            RL::ImageFlipHorizontal(&img);
            return RL::LoadTextureFromImage(img);
        };

        static const auto texture = load_texture_flipped(this->texture());
        return texture;
    }
};

template <typename SpriteType>
static const Spritesheet<SpriteType> spritesheet_for;

template <>
inline const Spritesheet<ThingSprite> spritesheet_for<ThingSprite>{6, 1, "assets/spritesheet.png"};

template <>
inline const Spritesheet<Tile> spritesheet_for<Tile>{16, 1, "assets/tilesheet.png"};

template <typename SpriteType>
struct TintedSprite {
    int sprite_idx;
    RL::Color tint;

    TintedSprite() = delete;

    TintedSprite(int idx, RL::Color tint) : sprite_idx(idx), tint(tint) {}
    TintedSprite(int idx) : TintedSprite(idx, RL::WHITE) {}
};

template <typename SpriteType>
void draw(const TintedSprite<SpriteType>& sprite, RL::Vector2 position) {
    const auto& spritesheet = spritesheet_for<SpriteType>;

    static const auto sheet = spritesheet.texture(), sheet_flipped = spritesheet.texture_flipped();

    RL::Vector2 px_position;
    px_position.x = position.x * SPRITE_DIM;
    px_position.y = position.y * SPRITE_DIM;

    const auto sprite_idx = std::abs(sprite.sprite_idx) - 1;

    RL::Rectangle source;
    source.width = source.height = SPRITE_DIM;

    const auto col = static_cast<int>(sprite_idx % spritesheet.width);

    if (sprite.sprite_idx < 0) {
        source.x = (spritesheet.width - 1 - col) * SPRITE_DIM;
    } else {
        source.x = col * SPRITE_DIM;
    }

    source.y = static_cast<int>(sprite_idx / spritesheet.width) * SPRITE_DIM;

    const auto active_sheet = sprite.sprite_idx < 0 ? sheet_flipped : sheet;
    RL::DrawTextureRec(active_sheet, source, px_position, sprite.tint);
}
