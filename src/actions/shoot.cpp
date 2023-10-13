#include "actions.hpp"
#include "line.hpp"
#include "things.hpp"

void Shoot::perform(Thing& actor) {
  projectile->x = actor.x;
  projectile->y = actor.y;

  projectile->trajectory = rasterize(projectile->x, projectile->y,
                                     projectile->dest_x, projectile->dest_y);

  spawn_queue.push_back(std::move(projectile));
}
