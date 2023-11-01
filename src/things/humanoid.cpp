#include <utility>

#include "actions.hpp"
#include "camera.hpp"
#include "grid.hpp"
#include "items.hpp"
#include "raylib.h"
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
    // TODO: flip correctly when going up/down too.
    const auto gun = dir == Direction::LEFT ? -ThingSprite::GUN : ThingSprite::GUN;
    return {{ThingSprite::MAN, body_color}, {gun}};
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

    switch (dir) {
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

    if (RL::IsKeyDown(RL::KEY_LEFT)) {
        ongoing.reset(new Move(Direction::LEFT, movement_length));
    } else if (RL::IsKeyDown(RL::KEY_RIGHT)) {
        ongoing.reset(new Move(Direction::RIGHT, movement_length));
    } else if (RL::IsKeyDown(RL::KEY_UP)) {
        ongoing.reset(new Move(Direction::UP, movement_length));
    } else if (RL::IsKeyDown(RL::KEY_DOWN)) {
        ongoing.reset(new Move(Direction::DOWN, movement_length));
    }
}

void Enemy::act() {
    // TODO: add AI.
}
