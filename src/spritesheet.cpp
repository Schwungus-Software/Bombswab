#include "spritesheet.hpp"

void draw(Sprite sprite, RL::Vector2 position, RL::Color tint) {
  static const auto spritesheet = RL::LoadTexture("assets/spritesheet.png");

  RL::Vector2 px_position;
  px_position.x = position.x * SPRITE_DIM;
  px_position.y = position.y * SPRITE_DIM;

  const auto sprite_idx = static_cast<int>(sprite);

  RL::Rectangle source;
  source.width = source.height = SPRITE_DIM;
  source.x = static_cast<int>(sprite_idx % SPRITESHEET_WIDTH) * SPRITE_DIM;
  source.y = static_cast<int>(sprite_idx / SPRITESHEET_WIDTH) * SPRITE_DIM;

  RL::DrawTextureRec(spritesheet, source, px_position, tint);
}
