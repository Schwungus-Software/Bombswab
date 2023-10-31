#include "audio.hpp"

RL::Sound footstep1, footstep2, footstep3, footstep4, footstep5, footstep6,
    rifle_fire, human_die, explode1, explode2, explode3;

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
    rifle_fire = RL::LoadSound("assets/sounds/rifle_fire.wav");
    human_die = RL::LoadSound("assets/sounds/human_die.wav");
    explode1 = RL::LoadSound("assets/sounds/explode1.wav");
    explode2 = RL::LoadSound("assets/sounds/explode2.wav");
    explode3 = RL::LoadSound("assets/sounds/explode3.wav");

    ready = true;
}

void play_sound_global(const RL::Sound& snd) { RL::PlaySound(snd); }

void play_sound_at(const RL::Sound& snd, RL::Vector2) {
    // TODO: implement with panning.
    RL::PlaySound(snd);
}
