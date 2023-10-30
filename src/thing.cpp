#include "thing.hpp"
#include "actions.hpp"

Thing::Thing(int x, int y)
    : x(x), y(y), ongoing(new Noop), max_health(1), cur_health(1), ghost(false),
      deletion_mark(false), stepped(false) {}

void Thing::tick() {
    think();

    ongoing->tick(*this);

    if (ongoing->length == 0 && !deletion_mark) {
        ongoing.reset(new Noop);
        act();
    }
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

void Thing::play_sound(RL::Sound snd) { play_sound_global(snd); }

void Thing::play_sound_local(RL::Sound snd) { play_sound_at(snd, pos()); }

RL::Vector2 Thing::pos() {
    return {static_cast<float>(x), static_cast<float>(y)};
}

void Action::tick(Thing& actor) {
    if (length-- == 1) {
        perform(actor);
    }
}
