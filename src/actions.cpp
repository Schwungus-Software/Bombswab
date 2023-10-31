#include "actions.hpp"

void Action::tick(Thing& actor) {
    if (length-- == 1) {
        perform(actor);
    }
}
