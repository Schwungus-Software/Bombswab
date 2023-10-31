#include "things.hpp"
#include "actions.hpp"
#include "grid.hpp"
#include "weapons.hpp"

void tick_things() {
    for (const auto& thing : things) {
        thing->tick();
    }

    grid.tick();

    // TODO: revise when the time comes.
    while (!spawn_queue.empty()) {
        things.push_back(std::unique_ptr<Thing>(spawn_queue.back()));
        spawn_queue.pop_back();
    }

    std::erase_if(things,
                  [](const auto& thing) { return thing->deletion_mark; });
}

void draw_things() {
    for (const auto& thing : things) {
        const auto& tile_at = grid.tile_at(thing->pos());

        if (tile_at.is_closed()) {
            continue;
        }

        const auto layers = thing->draw();

        for (const auto& layer : layers) {
            draw<ThingSprite>(layer, thing->pos());
        }
    }
}

Thing::Thing(int x, int y)
    : x(x), y(y), ongoing(new Noop), max_health(1), cur_health(1), ghost(false),
      deletion_mark(false), stepped(false) {}

void Thing::tick() {
    if (weapon.get() != nullptr && weapon->turns_until_ready > 0) {
        weapon->turns_until_ready--;
    }

    think();

    ongoing->tick(*this);

    if (ongoing->length == 0 && !deletion_mark) {
        ongoing.reset(new Noop);
        act();
    }
}

void Thing::collide() { ongoing.reset(new Die); }

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

Thing* Thing::collide_at(bool ghost_bypass) {
    for (const auto& thing : things) {
        if (collides_with(*thing, ghost_bypass)) {
            return thing.get();
        }
    }

    return nullptr;
}

void Thing::play_sound(const RL::Sound& snd) { play_sound_global(snd); }

void Thing::play_sound_local(const RL::Sound& snd) {
    play_sound_at(snd, pos());
}

Thing::~Thing() = default;

RL::Vector2 Thing::pos() {
    return {static_cast<float>(x), static_cast<float>(y)};
}
