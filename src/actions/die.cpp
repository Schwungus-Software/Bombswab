#include "actions.hpp"

void Die::perform(Thing& actor) {
  actor.before_death();
  actor.deletion_mark = true;
}
