#include "actions.hpp"
#include "line.hpp"
#include "things.hpp"
#include "weapons.hpp"

void Shoot::perform(Thing& actor) {
    const auto& weapon_item = actor.hand_slot(slot).contents.get();

    if (weapon_item == nullptr) {
        return;
    }

    const auto weapon = dynamic_cast<AbstractWeapon*>(weapon_item);

    if (weapon == nullptr) {
        return;
    }

    if (weapon->turns_until_ready > 0) {
        return;
    }

    const auto projectile = weapon->spawn_projectile(destination);

    projectile->trajectory = rasterize(actor.x, actor.y, projectile->dest_x, projectile->dest_y);

    projectile->x = projectile->trajectory[0].x;
    projectile->y = projectile->trajectory[0].y;

    const auto dx = projectile->dest_x - actor.x;
    const auto dy = projectile->dest_y - actor.y;

    if (std::abs(dx) >= std::abs(dy)) {
        if (dx >= 0) {
            actor.action_dir = Direction::RIGHT;
        } else {
            actor.action_dir = Direction::LEFT;
        }
    } else {
        if (dy >= 0) {
            actor.action_dir = Direction::DOWN;
        } else {
            actor.action_dir = Direction::UP;
        }
    }

    weapon->turns_until_ready = weapon->shoot_cooldown;

    spawn_queue.push_back(std::move(projectile));
    actor.play_sound_local(rifle_fire);
}
