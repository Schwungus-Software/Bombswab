#include "things.hpp"

std::vector<Thing::Sprite> Corpse::draw() {
    return {ThingSprite::CORPSE};
}
