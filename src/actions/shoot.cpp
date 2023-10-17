#include "actions.hpp"
#include "line.hpp"
#include "things.hpp"

void Shoot::perform(Thing& actor) {
    projectile->trajectory =
        rasterize(actor.x, actor.y, projectile->dest_x, projectile->dest_y);

    projectile->x = projectile->trajectory[0].x;
    projectile->y = projectile->trajectory[0].y;

    spawn_queue.push_back(std::move(projectile));
    actor.play_sound_local(rifle_fire);
}
