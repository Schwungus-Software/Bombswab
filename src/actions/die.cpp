#include "actions.hpp"

void Die::perform(Thing& actor) { actor.deletion_mark = true; }
