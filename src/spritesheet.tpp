#pragma once

#include <cmath>
#include <cstdint>
#include <stdexcept>

#include "raylib.h"

#include "misc.hpp"

const int SPRITE_DIM = 16;

template <typename SpriteType>
class Spritesheet {
  public:
    const int width, height;
    const char* sheet_path;

    constexpr Spritesheet() : Spritesheet(0, 0, nullptr) {}

    constexpr Spritesheet(const int width, const int height, const char* sheet_path)
        : width(width), height(height), sheet_path(sheet_path) {}

    Texture2D texture() const {
        if (sheet_path == nullptr) {
            throw std::invalid_argument("sheet_path cannot be null; this means you're using a "
                                        "spritesheet that doesn't have a defined set of sprites");
        }

        static const auto texture = LoadTexture(sheet_path);
        return texture;
    }

    Texture2D texture_flipped(SpriteFlip flip) const {
        const auto load_texture_flipped = [this](Texture2D texture, SpriteFlip flip) {
            const auto img = LoadImageFromTexture(texture);

            auto result = ImageCopy(img);
            ImageClearBackground(&result, {0, 0, 0, 0});

            for (float y = 0.0; y < height; y += 1.0) {
                for (float x = 0.0; x < width; x += 1.0) {
                    const Rectangle dest{x * SPRITE_DIM, y * SPRITE_DIM, SPRITE_DIM, SPRITE_DIM};

                    auto flipped = ImageFromImage(img, dest);

                    switch (flip) {
                        case SpriteFlip::DEG_270:
                        case SpriteFlip::NEG_270:
                            ImageRotateCW(&flipped);
                        case SpriteFlip::DEG_180:
                        case SpriteFlip::NEG_180:
                            ImageRotateCW(&flipped);
                        case SpriteFlip::DEG_90:
                        case SpriteFlip::NEG_90:
                            ImageRotateCW(&flipped);
                        case SpriteFlip::DEG_0:
                        case SpriteFlip::NEG_0:
                            // Do nothing.
                            break;
                    }

                    switch (flip) {
                        case SpriteFlip::NEG_0:
                        case SpriteFlip::NEG_180:
                            ImageFlipVertical(&flipped);
                            break;
                        case SpriteFlip::NEG_90:
                        case SpriteFlip::NEG_270:
                            ImageFlipHorizontal(&flipped);
                            break;
                        default:
                            // Do nothing.
                            break;
                    }

                    ImageDraw(&result, flipped, {0, 0, SPRITE_DIM, SPRITE_DIM}, dest, WHITE);
                }
            }

            return LoadTextureFromImage(result);
        };

        return load_texture_flipped(this->texture(), flip);
    }
};

template <typename SpriteType>
static const Spritesheet<SpriteType> spritesheet_for;

template <typename SpriteType>
struct TintedSprite {
    int sprite_idx;
    Color tint;

    SpriteFlip flip;
    float offset, cross;

    TintedSprite() = delete;

    TintedSprite(int idx, SpriteFlip flip = SpriteFlip::DEG_0) : TintedSprite(idx, WHITE, flip) {}

    TintedSprite(int idx, Color tint, SpriteFlip flip = SpriteFlip::DEG_0)
        : sprite_idx(idx), tint(tint), flip(flip), offset(0.0), cross(0.0) {}
};

template <typename SpriteType>
void draw(const TintedSprite<SpriteType>& sprite, Vector2 position) {
    const auto& spritesheet = spritesheet_for<SpriteType>;

    static const auto sheet_deg_0 = spritesheet.texture_flipped(SpriteFlip::DEG_0),
                      sheet_neg_0 = spritesheet.texture_flipped(SpriteFlip::NEG_0),
                      sheet_deg_90 = spritesheet.texture_flipped(SpriteFlip::DEG_90),
                      sheet_neg_90 = spritesheet.texture_flipped(SpriteFlip::NEG_90),
                      sheet_deg_180 = spritesheet.texture_flipped(SpriteFlip::DEG_180),
                      sheet_neg_180 = spritesheet.texture_flipped(SpriteFlip::NEG_180),
                      sheet_deg_270 = spritesheet.texture_flipped(SpriteFlip::DEG_270),
                      sheet_neg_270 = spritesheet.texture_flipped(SpriteFlip::NEG_270);

    Rectangle source;
    source.width = source.height = SPRITE_DIM;

    source.x = static_cast<int>(sprite.sprite_idx % spritesheet.width) * SPRITE_DIM;
    source.y = static_cast<int>(sprite.sprite_idx / spritesheet.width) * SPRITE_DIM;

    Texture active_sheet;

    Vector2 px_position;
    px_position.x = position.x;
    px_position.y = position.y;

    switch (sprite.flip) {
        case SpriteFlip::DEG_0:
            active_sheet = sheet_deg_0;
            px_position.x += sprite.offset;
            px_position.y -= sprite.cross;
            break;
        case SpriteFlip::NEG_0:
            active_sheet = sheet_neg_0;
            px_position.x += sprite.offset;
            px_position.y += sprite.cross;
            break;
        case SpriteFlip::DEG_90:
            active_sheet = sheet_deg_90;
            px_position.x -= sprite.cross;
            px_position.y += sprite.offset;
            break;
        case SpriteFlip::NEG_90:
            active_sheet = sheet_neg_90;
            px_position.x += sprite.cross;
            px_position.y += sprite.offset;
            break;
        case SpriteFlip::DEG_180:
            active_sheet = sheet_deg_180;
            px_position.x -= sprite.offset;
            px_position.y += sprite.cross;
            break;
        case SpriteFlip::NEG_180:
            active_sheet = sheet_neg_180;
            px_position.x -= sprite.offset;
            px_position.y -= sprite.cross;
            break;
        case SpriteFlip::DEG_270:
            active_sheet = sheet_deg_270;
            px_position.x += sprite.cross;
            px_position.y -= sprite.offset;
            break;
        case SpriteFlip::NEG_270:
            active_sheet = sheet_neg_270;
            px_position.x -= sprite.cross;
            px_position.y -= sprite.offset;
            break;
    }

    px_position.x *= SPRITE_DIM;
    px_position.y *= SPRITE_DIM;

    DrawTextureRec(active_sheet, source, px_position, sprite.tint);
}
