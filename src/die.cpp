#include "actions.hpp"
#include "things.hpp"

void Die::perform(Thing& actor) {
    actor.died();
    actor.deletion_mark = true;
}
