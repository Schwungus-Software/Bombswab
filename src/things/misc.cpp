#include "spritesheet.hpp"
#include "things.hpp"

std::vector<TintedSprite<ThingSprite>> Corpse::draw() {
    return {ThingSprite::CORPSE};
}
