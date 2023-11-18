#include "actions.hpp"
#include "things.hpp"

void Die::perform(Thing& actor) {
    actor.before_death();
    actor.deletion_mark = true;
}
