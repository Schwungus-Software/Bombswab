#include <cmath>

#include "spritesheet.hpp"

template <>
const Spritesheet<ThingSprite> spritesheet_for<ThingSprite>{
    6, 1, "assets/spritesheet.png"};

template <>
const Spritesheet<Tile> spritesheet_for<Tile>{16, 1, "assets/tilesheet.png"};

template <typename SpriteType>
RL::Texture2D Spritesheet<SpriteType>::texture() const {
    static const auto texture = RL::LoadTexture(sheet_path);
    return texture;
}

RL::Texture2D load_texture_flipped(RL::Texture2D texture) {
    auto img = RL::LoadImageFromTexture(texture);
    RL::ImageFlipHorizontal(&img);
    return RL::LoadTextureFromImage(img);
}

template <typename SpriteType>
RL::Texture2D Spritesheet<SpriteType>::texture_flipped() const {
    static const auto texture = load_texture_flipped(this->texture());
    return texture;
}

template <typename SpriteType>
void draw(const TintedSprite<SpriteType>& sprite, RL::Vector2 position) {
    const auto& spritesheet = spritesheet_for<SpriteType>;

    static const auto sheet = spritesheet.texture(),
                      sheet_flipped = spritesheet.texture_flipped();

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

template void draw<ThingSprite>(const TintedSprite<ThingSprite>&, RL::Vector2);
template void draw<Tile>(const TintedSprite<Tile>&, RL::Vector2);
