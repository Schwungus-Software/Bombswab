#include <utility>
#include <variant>

#include "actions.hpp"
#include "camera.hpp"
#include "items.hpp"
#include "keybinds.hpp"
#include "level.hpp"
#include "raylib.h"
#include "spritesheet.tpp"
#include "utils.tpp"
#include "weapons.hpp"

Humanoid::Humanoid(int x, int y, Color body_color, bool can_reveal_tiles)
    : Thing(x, y), body_color(body_color), can_reveal_tiles(can_reveal_tiles) {
    const auto rifle = new AssaultRifle;
    rifle->clip_slot->insert(new BulletClip(50));
    lh_slot->insert(rifle);

    const auto pistol = new Pistol;
    pistol->clip_slot->insert(new BulletClip(10));
    rh_slot->insert(pistol);

    const auto clip = new BulletClip(100);
    pockets[3]->insert(clip);
}

std::vector<Thing::Sprite> Humanoid::draw() {
    std::vector<Sprite> layers;

    const auto push_guy = [this, &layers]() { layers.push_back({ThingSprite::MAN, body_color}); };

    const auto vertical = [this, &layers](ID<ItemSlot> slot, const bool left) {
        if (slot->empty()) {
            return;
        }

        for (auto sprite : slot->peek()->sprite) {
            sprite.flip = left ? ::flip(action_dir_to_flip()) : action_dir_to_flip();
            sprite.offset += 6.0 / SPRITE_DIM;
            sprite.cross += 4.0 / SPRITE_DIM;
            layers.push_back(sprite);
        }
    };

    const auto horizontal = [this, &layers](const ID<ItemSlot> slot, const bool back) {
        if (slot->empty()) {
            return;
        }

        for (auto sprite : slot->peek()->sprite) {
            sprite.flip = action_dir_to_flip();

            if (back) {
                sprite.offset += 5.0 / SPRITE_DIM;
                sprite.cross -= 2.0 / SPRITE_DIM;
            } else {
                sprite.offset += 6.0 / SPRITE_DIM;
                sprite.cross += 1.0 / SPRITE_DIM;
            }

            layers.push_back(sprite);
        }
    };

    switch (action_dir) {
        case Direction::UP:
            push_guy();
            vertical(lh_slot, true);
            vertical(rh_slot, false);
            break;
        case Direction::DOWN:
            push_guy();
            vertical(rh_slot, true);
            vertical(lh_slot, false);
            break;
        case Direction::RIGHT:
            horizontal(lh_slot, true);
            push_guy();
            horizontal(rh_slot, false);
            break;
        case Direction::LEFT:
            horizontal(rh_slot, true);
            push_guy();
            horizontal(lh_slot, false);
            break;
    }

    return layers;
}

void Humanoid::step() {
    if (can_reveal_tiles) {
        level.grid.open(pos());
    }

    stepped = !stepped;

    if (stepped) {
        const auto footstep = pick(footsteps);
        play_sound_local(*footstep);
    }
}

void Humanoid::collide() {
    const auto& tile = level.grid.tile_at(pos());

    if (can_reveal_tiles) {
        level.grid.open(pos());
    }

    switch (walk_dir) {
        case Direction::LEFT:
            x++;
            break;
        case Direction::RIGHT:
            x--;
            break;
        case Direction::UP:
            y++;
            break;
        case Direction::DOWN:
            y--;
            break;
    }
}

void Humanoid::pain() {
    const auto pain = pick(pains);
    play_sound_local(*pain);
}

void Humanoid::died() {
    play_sound_local(human_die);

    auto corpse = new Corpse(x, y);

    corpse->max_health = max_health;
    corpse->cur_health = std::max(1, max_health / 2);

    level.spawn_thing(corpse);
}

void Player::act() {
    camera_center = pos();
    camera_center.x *= SPRITE_DIM;
    camera_center.y *= SPRITE_DIM;

    for (const auto& keybind : keybinds) {
        if (keybind.bind.is_active() && keybind.condition(*this)) {
            const auto result = keybind.action(*this);
            const auto fallthrough = std::holds_alternative<Fallthrough>(result);

            if (!fallthrough) {
                break;
            }
        }
    }
}

std::vector<Thing::Sprite> Player::draw() {
    auto layers = Humanoid::draw();

    if (last_selected.valid()) {
        float i = (pockets.size() * -0.5) + 0.5;

        for (const auto& slot : pockets) {
            auto cell = Thing::Sprite(ThingSprite::CELL);

            cell.offset += i;
            cell.cross = 1.0;
            layers.push_back(cell);

            if (!slot->empty()) {
                for (auto sprite : slot->peek()->sprite) {
                    sprite.offset += i;
                    sprite.cross = 1.0;
                    layers.push_back(sprite);
                }
            }

            ++i;
        }
    }

    return layers;
}

void Enemy::act() {
    // TODO: add AI.
}
