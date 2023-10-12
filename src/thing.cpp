#include "thing.hpp"

Thing::Thing(int x, int y) : x(x), y(y) { ongoing = std::make_unique<Noop>(); }

void Thing::tick() {
  ongoing->tick(*this);

  if (ongoing->length == 0) {
    ongoing.reset(new Noop);
    think();
  }
}

void Thing::play_sound(RL::Sound snd) {
    PlaySound(snd);
}

void Thing::play_sound_local(RL::Sound snd) {
    play_sound(snd);
}

void Action::tick(Thing& actor) {
  if (length-- == 1) {
    perform(actor);
  }
}
