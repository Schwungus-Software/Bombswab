#include <utility>

#include "actions.hpp"
#include "camera.hpp"
#include "grid.hpp"
#include "items.hpp"
#include "spritesheet.hpp"
#include "things.hpp"
#include "utils.hpp"
#include "weapons.hpp"

Humanoid::Humanoid(int x, int y, RL::Color body_color, bool can_reveal_tiles)
    : Thing(x, y), body_color(body_color), can_reveal_tiles(can_reveal_tiles) {
    const auto rifle = new Rifle;
    rifle->clip_slot.contents.reset(new BulletClip(50));
    lh_slot.contents.reset(rifle);

    const auto pistol = new Pistol;
    pistol->clip_slot.contents.reset(new BulletClip(10));
    rh_slot.contents.reset(pistol);
}

std::vector<Thing::Sprite> Humanoid::draw() {
    std::vector<Sprite> layers;

    const auto push_guy = [this, &layers]() { layers.push_back({ThingSprite::MAN, body_color}); };

    const auto vertical = [this, &layers](const ItemSlot& slot, const bool left) {
        if (slot.contents != nullptr) {
            for (auto sprite : slot.contents->draw()) {
                sprite.flip = left ? ::flip(action_dir_to_flip()) : action_dir_to_flip();
                sprite.offset += 6.0 / SPRITE_DIM;
                sprite.cross += 4.0 / SPRITE_DIM;
                layers.push_back(sprite);
            }
        }
    };

    const auto horizontal = [this, &layers](const ItemSlot& slot, const bool back) {
        if (slot.contents == nullptr) {
            return;
        }

        for (auto sprite : slot.contents->draw()) {
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
        grid.open(pos());
    }

    stepped = !stepped;

    if (stepped) {
        const auto footstep = pick(footsteps);
        play_sound_local(*footstep);
    }
}

void Humanoid::collide() {
    const auto& tile = grid.tile_at(pos());

    if (can_reveal_tiles) {
        grid.open(pos());
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

void Humanoid::before_death() {
    play_sound_local(human_die);

    auto corpse = new Corpse(x, y);

    corpse->max_health = max_health;
    corpse->cur_health = std::max(1, max_health / 2);

    spawn_queue.push_back(corpse);
}

void Player::act() {
    camera_center = pos();
    camera_center.x *= SPRITE_DIM;
    camera_center.y *= SPRITE_DIM;

    const int movement_length = 8;

    const std::vector<std::pair<RL::MouseButton, HandSlot>> weapon_slots{
        {RL::MOUSE_BUTTON_LEFT, HandSlot::LEFT},
        {RL::MOUSE_BUTTON_RIGHT, HandSlot::RIGHT},
    };

    for (const auto& pair : weapon_slots) {
        const auto& slot = hand_slot(pair.second);
        const auto item = slot.contents.get();

        if (item == nullptr) {
            continue;
        }

        const auto weapon = dynamic_cast<AbstractWeapon*>(item);

        if (weapon == nullptr) {
            continue;
        }

        if (!weapon->has_ammo()) {
            // TODO: play "no ammo" sound.
            continue;
        }

        if (weapon->turns_until_ready > 0) {
            continue;
        }

        if (RL::IsMouseButtonDown(pair.first)) {
            const auto dest = mouse_to_grid();
            ongoing.reset(new Shoot(dest, pair.second));
            return;
        }
    }

    if (RL::IsKeyDown(RL::KEY_A)) {
        ongoing.reset(new Move(Direction::LEFT, movement_length));
    } else if (RL::IsKeyDown(RL::KEY_D)) {
        ongoing.reset(new Move(Direction::RIGHT, movement_length));
    } else if (RL::IsKeyDown(RL::KEY_W)) {
        ongoing.reset(new Move(Direction::UP, movement_length));
    } else if (RL::IsKeyDown(RL::KEY_S)) {
        ongoing.reset(new Move(Direction::DOWN, movement_length));
    }
}

void Enemy::act() {
    // TODO: add AI.
}
