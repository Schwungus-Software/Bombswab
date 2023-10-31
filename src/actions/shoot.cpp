#include "actions.hpp"
#include "line.hpp"
#include "things.hpp"
#include "weapons.hpp"

void Shoot::perform(Thing& actor) {
    if (actor.weapon.get() == nullptr) {
        return;
    }

    if (actor.weapon->turns_until_ready > 0) {
        return;
    }

    const auto projectile = actor.weapon->spawn_projectile(destination);

    projectile->trajectory =
        rasterize(actor.x, actor.y, projectile->dest_x, projectile->dest_y);

    projectile->x = projectile->trajectory[0].x;
    projectile->y = projectile->trajectory[0].y;

    actor.weapon->turns_until_ready = actor.weapon->shoot_cooldown;

    spawn_queue.push_back(std::move(projectile));
    actor.play_sound_local(rifle_fire);
}
