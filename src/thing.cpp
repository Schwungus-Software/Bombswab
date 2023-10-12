#include "thing.hpp"

Thing::Thing(int x, int y) : x(x), y(y) { ongoing = std::make_unique<Noop>(); }

void Thing::tick() {
  ongoing->tick(*this);

  if (ongoing->length == 0) {
    ongoing.reset(new Noop);
    think();
  }
}

void Action::tick(Thing& actor) {
  if (length-- == 1) {
    perform(actor);
  }
}
