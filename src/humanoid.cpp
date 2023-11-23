#include <utility>

#include "actions.hpp"
#include "camera.hpp"
#include "items.hpp"
#include "level.hpp"
#include "spritesheet.tpp"
#include "utils.tpp"
#include "weapons.hpp"

Humanoid::Humanoid(int x, int y, Color body_color, bool can_reveal_tiles)
    : Thing(x, y), body_color(body_color), can_reveal_tiles(can_reveal_tiles) {
    const auto rifle = new Rifle;
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

        for (auto sprite : slot->peek()->draw()) {
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

        for (auto sprite : slot->peek()->draw()) {
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

    const std::vector<std::pair<KeyboardKey, ID<ItemSlot>>> item_slots{
        {KEY_Q, lh_slot},      {KEY_E, rh_slot},        {KEY_ONE, pockets[0]},
        {KEY_TWO, pockets[1]}, {KEY_THREE, pockets[2]}, {KEY_FOUR, pockets[3]},
    };

    if (IsKeyPressed(KEY_SPACE)) {
        if (!last_selected.valid()) { // select whatever's on the ground
            for (const auto& thing : level.things) {
                const auto drop = dynamic_cast<ItemDrop*>(thing.get());

                if (drop != nullptr) {
                    last_selected = drop->internal_slot;
                    break;
                }
            }
        } else if (!last_selected->empty()) { // activate
            const auto action = last_selected->peek()->activate(*this);

            if (action != nullptr) {
                ongoing.reset(action);
            }

            return;
        } else { // deselect since it's empty anyways
            last_selected.invalidate();
            return;
        }
    }

    if (IsKeyPressed(KEY_G) && last_selected.valid() && !last_selected->empty()) {
        // TODO: drop on the ground.
        last_selected->trash();
        return;
    }

    for (const auto& pair : item_slots) {
        if (!IsKeyPressed(pair.first)) {
            continue;
        }

        auto slot = pair.second;

        if (last_selected.valid()) {
            if (last_selected->peek() != nullptr && slot->peek() != nullptr) {
                const auto action = slot->peek()->insert(*this, last_selected);

                if (action != nullptr) {
                    ongoing.reset(action);
                }

                last_selected.invalidate();

                return;
            } else if (last_selected->peek() != nullptr && slot->peek() == nullptr) {
                slot->insert(last_selected->take());
                last_selected.invalidate();

                return;
            }
        } else {
            last_selected = slot;
            return;
        }
    }

    const std::vector<std::pair<MouseButton, HandSlot>> weapon_slots{
        {MOUSE_BUTTON_LEFT, HandSlot::LEFT},
        {MOUSE_BUTTON_RIGHT, HandSlot::RIGHT},
    };

    for (const auto& pair : weapon_slots) {
        const auto& slot = hand_slot(pair.second);
        const auto item = slot->peek();

        if (item == nullptr) {
            continue;
        }

        const auto weapon = dynamic_cast<AbstractWeapon*>(item);

        if (weapon == nullptr) {
            continue;
        }

        if (weapon->turns_until_ready > 0) {
            continue;
        }

        if (IsMouseButtonDown(pair.first)) {
            const auto dest = mouse_to_grid();
            ongoing.reset(new Shoot(dest, pair.second));
            last_selected.invalidate();
            return;
        }
    }

    const int movement_length = 8;

    if (IsKeyDown(KEY_A)) {
        ongoing.reset(new Move(Direction::LEFT, movement_length));
    } else if (IsKeyDown(KEY_D)) {
        ongoing.reset(new Move(Direction::RIGHT, movement_length));
    } else if (IsKeyDown(KEY_W)) {
        ongoing.reset(new Move(Direction::UP, movement_length));
    } else if (IsKeyDown(KEY_S)) {
        ongoing.reset(new Move(Direction::DOWN, movement_length));
    } else {
        return;
    }

    last_selected.invalidate();
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
                for (auto sprite : slot->peek()->draw()) {
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
