#include "audio.hpp"

RL::Sound footstep1 = {0};
RL::Sound footstep2 = {0};
RL::Sound footstep3 = {0};
RL::Sound footstep4 = {0};
RL::Sound footstep5 = {0};
RL::Sound footstep6 = {0};

void load_sounds() {
  static bool ready = false;

  if (ready) {
    return;
  }

  footstep1 = RL::LoadSound("assets/sounds/footstep1.wav");
  footstep2 = RL::LoadSound("assets/sounds/footstep2.wav");
  footstep3 = RL::LoadSound("assets/sounds/footstep3.wav");
  footstep4 = RL::LoadSound("assets/sounds/footstep4.wav");
  footstep5 = RL::LoadSound("assets/sounds/footstep5.wav");
  footstep6 = RL::LoadSound("assets/sounds/footstep6.wav");

  ready = true;
}
