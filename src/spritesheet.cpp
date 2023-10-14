#include <cmath>

#include "spritesheet.hpp"

RL::Texture2D load_flipped_spritesheet(const RL::Texture2D& orig) {
  auto img = RL::LoadImageFromTexture(orig);
  RL::ImageFlipHorizontal(&img);
  return RL::LoadTextureFromImage(img);
}

void draw(TintedSprite sprite, RL::Vector2 position) {
  static const auto spritesheet = RL::LoadTexture("assets/spritesheet.png");
  static const auto flipped_spritesheet = load_flipped_spritesheet(spritesheet);

  RL::Vector2 px_position;
  px_position.x = position.x * SPRITE_DIM;
  px_position.y = position.y * SPRITE_DIM;

  const auto sprite_idx = std::abs(sprite.sprite_idx) - 1;

  RL::Rectangle source;
  source.width = source.height = SPRITE_DIM;

  if (sprite.sprite_idx < 0) {
    const auto col = static_cast<int>(sprite_idx % SPRITESHEET_WIDTH);
    source.x = (SPRITESHEET_WIDTH - 1 - col) * SPRITE_DIM;
  } else {
    source.x = static_cast<int>(sprite_idx % SPRITESHEET_WIDTH) * SPRITE_DIM;
  }

  source.y = static_cast<int>(sprite_idx / SPRITESHEET_WIDTH) * SPRITE_DIM;

  const auto active_spritesheet =
      sprite.sprite_idx < 0 ? flipped_spritesheet : spritesheet;

  RL::DrawTextureRec(active_spritesheet, source, px_position, sprite.tint);
}
