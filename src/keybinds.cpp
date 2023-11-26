#include <map>

#include "raylib.h"

#include "keybinds.hpp"
#include "level.hpp"
#include "misc.hpp"
#include "weapons.hpp"

static const int MOVEMENT_LENGTH = 8;

bool Bind::is_active() const {
    if (std::holds_alternative<Press>(kind)) {
        const auto key = std::get<Press>(kind).key;

        if (IsKeyPressed(key)) {
            return true;
        }
    } else if (std::holds_alternative<Repeat>(kind)) {
        const auto key = std::get<Repeat>(kind).key;

        if (IsKeyDown(key)) {
            return true;
        }
    } else if (std::holds_alternative<Click>(kind)) {
        const auto button = std::get<Click>(kind).button;

        if (IsMouseButtonPressed(button)) {
            return true;
        }
    } else if (std::holds_alternative<Hold>(kind)) {
        const auto button = std::get<Hold>(kind).button;

        if (IsMouseButtonDown(button)) {
            return true;
        }
    }

    return false;
}

#define COND(c) [](const auto& player) { return (c); }

static Binding::Result select_from_ground(Thing& player) {
    for (const auto& thing : level.things) {
        const auto drop = dynamic_cast<ItemDrop*>(thing.get());

        if (drop == nullptr) {
            continue;
        }

        if (player.collides_with(*drop, true)) {
            player.last_selected = drop->internal_slot;
            break;
        }
    }

    return Finished();
}

static Binding::Result activate(Thing& player) {
    const auto action = player.last_selected->peek()->activate(player);

    if (action != nullptr) {
        player.ongoing.reset(action);
    }

    return Finished();
}

static Binding::Result trash(Thing& player) {
    // TODO: drop on the ground instead.
    player.last_selected->trash();
    player.last_selected.invalidate();
    return Finished();
}

static ID<ItemSlot> get_slot(Thing& thing, KeyboardKey key) {
    const std::map<KeyboardKey, ID<ItemSlot>> item_slots = {
        {KEY_Q, thing.lh_slot},      {KEY_E, thing.rh_slot},        {KEY_ONE, thing.pockets[0]},
        {KEY_TWO, thing.pockets[1]}, {KEY_THREE, thing.pockets[2]}, {KEY_FOUR, thing.pockets[3]},
    };

    return item_slots.at(key);
}

static Binding slot(KeyboardKey key) {
    const auto action = [key](Thing& player) {
        auto slot = get_slot(player, key);

        if (player.last_selected.valid()) {
            if (player.last_selected->peek() != nullptr && slot->peek() != nullptr) {
                const auto action = slot->peek()->insert(player, player.last_selected);

                if (action != nullptr) {
                    player.ongoing.reset(action);
                }

                player.last_selected.invalidate();
            } else if (player.last_selected->peek() != nullptr && slot->peek() == nullptr) {
                slot->insert(player.last_selected->take());
                player.last_selected.invalidate();
            }
        } else {
            player.last_selected = slot;
        }

        return Finished();
    };

    return {Press{key}, action};
}

// TODO: redo for more intricate item interactions.
static Binding shoot(MouseButton button) {
    const auto action = [button](Thing& player) -> Binding::Result {
        const std::map<MouseButton, HandSlot> weapon_slots{
            {MOUSE_BUTTON_LEFT, HandSlot::LEFT},
            {MOUSE_BUTTON_RIGHT, HandSlot::RIGHT},
        };

        const auto h_slot = weapon_slots.at(button);
        const auto& slot = player.hand_slot(h_slot);
        const auto item = slot->peek();

        if (item == nullptr) {
            return Fallthrough();
        }

        const auto weapon = dynamic_cast<AbstractWeapon*>(item);

        if (weapon == nullptr) {
            return Fallthrough();
        }

        if (weapon->turns_until_ready > 0) {
            return Fallthrough();
        }

        const auto dest = mouse_to_grid();
        player.ongoing.reset(new Shoot(dest, h_slot));
        player.last_selected.invalidate();

        return Finished();
    };

    return {Hold{button}, action};
}

static inline Binding::Action move(Direction dir) {
    return [dir](auto& player) {
        player.ongoing.reset(new Move(dir, MOVEMENT_LENGTH));
        player.last_selected.invalidate();
        return Finished();
    };
}

const std::vector<Binding> keybinds{
    {Press{KEY_SPACE}, select_from_ground, COND(!player.last_selected.valid())},
    {Press{KEY_SPACE}, activate, COND(!player.last_selected->empty())},
    {Press{KEY_SPACE},
     [](auto& p) {
         p.last_selected.invalidate();
         return Finished();
     }},
    {Press{KEY_G}, trash, COND(player.last_selected.valid() && !player.last_selected->empty())},
    slot(KEY_Q),
    slot(KEY_E),
    slot(KEY_ONE),
    slot(KEY_TWO),
    slot(KEY_THREE),
    slot(KEY_FOUR),
    shoot(MOUSE_BUTTON_LEFT),
    shoot(MOUSE_BUTTON_RIGHT),
    {Repeat{KEY_A}, move(Direction::LEFT)},
    {Repeat{KEY_D}, move(Direction::RIGHT)},
    {Repeat{KEY_W}, move(Direction::UP)},
    {Repeat{KEY_S}, move(Direction::DOWN)},
};

#undef COND
