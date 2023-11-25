#include "things.hpp"
#include "actions.hpp"
#include "grid.hpp"
#include "level.hpp"
#include "weapons.hpp"

Thing::Thing(int x, int y)
    : x(x), y(y), ongoing(new Noop), max_health(1), cur_health(1), ghost(false), deletion_mark(false), stepped(false),
      walk_dir(Direction::RIGHT), action_dir(Direction::RIGHT) {
    last_selected.invalidate();
}

void Thing::tick() {
    lh_slot->tick();
    rh_slot->tick();

    for (auto& slot : pockets) {
        slot->tick();
    }

    think();

    ongoing->tick(*this);

    if (ongoing->length == 0 && !deletion_mark) {
        ongoing.reset(new Noop);
        act();
    }
}

void Thing::collide() {
    ongoing.reset(new Die);
}

SpriteFlip Thing::action_dir_to_flip() {
    switch (action_dir) {
        case Direction::LEFT:
            return SpriteFlip::NEG_180;
        case Direction::RIGHT:
            return SpriteFlip::DEG_0;
        case Direction::UP:
            return SpriteFlip::NEG_270;
        case Direction::DOWN:
            return SpriteFlip::DEG_90;
    }

    // To silence a warning.
    return SpriteFlip::DEG_0;
}

bool Thing::damage(int amount) {
    cur_health -= amount;

    if (deletion_mark) {
        return true;
    }

    if (cur_health <= 0) {
        ongoing.reset(new Die);
        return true;
    }

    pain();
    return false;
}

bool Thing::collides_with(const Thing& another, bool ghost_bypass) {
    if (&another == this) {
        return false;
    }

    // If NOT dying.
    // TODO: find a more idiomatic way to perform the instanceof check.
    if (dynamic_cast<Die*>(ongoing.get()) != nullptr) {
        return false;
    }

    if (x == another.x && y == another.y) {
        if (dynamic_cast<Die*>(another.ongoing.get()) == nullptr) {
            if (ghost_bypass || !another.ghost) {
                return true;
            }
        }
    }

    return false;
}

Thing* Thing::intersect_at(bool ghost_bypass) {
    for (const auto& thing : level.things) {
        if (collides_with(*thing, ghost_bypass)) {
            return thing.get();
        }
    }

    return nullptr;
}

void Thing::play_sound(const Sound& snd) {
    play_sound_global(snd);
}

void Thing::play_sound_local(const Sound& snd) {
    play_sound_at(snd, pos());
}

ID<ItemSlot> Thing::hand_slot(HandSlot hand_slot) {
    if (hand_slot == HandSlot::LEFT) {
        return lh_slot;
    } else {
        return rh_slot;
    }
}

Vector2 Thing::pos() {
    return {static_cast<float>(x), static_cast<float>(y)};
}

Thing::~Thing() = default;

void ItemDrop::think() {
    if (internal_slot->empty()) {
        deletion_mark = true;
    } else {
        internal_slot->tick();
    }
}

std::vector<Thing::Sprite> ItemDrop::draw() {
    return internal_slot->peek()->sprite;
}

std::vector<Thing::Sprite> Corpse::draw() {
    return {ThingSprite::CORPSE};
}
