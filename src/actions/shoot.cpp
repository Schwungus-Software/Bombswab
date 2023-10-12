#include "actions.hpp"
#include "things.hpp"

void Shoot::perform(Thing& actor) {
  projectile->x = actor.x;
  projectile->y = actor.y;
  spawn_queue.push_back(std::move(projectile));
}
