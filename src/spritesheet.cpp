#include "spritesheet.hpp"

SpriteFlip flip(const SpriteFlip& orig) {
    switch (orig) {
        case SpriteFlip::DEG_0:
            return SpriteFlip::NEG_0;
        case SpriteFlip::NEG_0:
            return SpriteFlip::DEG_0;
        case SpriteFlip::DEG_90:
            return SpriteFlip::NEG_90;
        case SpriteFlip::NEG_90:
            return SpriteFlip::DEG_90;
        case SpriteFlip::DEG_180:
            return SpriteFlip::NEG_180;
        case SpriteFlip::NEG_180:
            return SpriteFlip::DEG_180;
        case SpriteFlip::DEG_270:
            return SpriteFlip::NEG_270;
        case SpriteFlip::NEG_270:
            return SpriteFlip::DEG_270;
        default:
            return SpriteFlip::DEG_0;
    }
}
