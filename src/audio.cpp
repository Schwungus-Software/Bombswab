#include "audio.hpp"

RL::Sound footstep1 = {0};
RL::Sound footstep2 = {0};
RL::Sound footstep3 = {0};
RL::Sound footstep4 = {0};
RL::Sound footstep5 = {0};
RL::Sound footstep6 = {0};
RL::Sound rifle_fire = {0};
RL::Sound human_die = {0};
RL::Sound explode1 = {0};
RL::Sound explode2 = {0};
RL::Sound explode3 = {0};

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

void play_sound_global(RL::Sound snd) { RL::PlaySound(snd); }

void play_sound_at(RL::Sound snd, RL::Vector2) {
    // TODO: implement with panning.
    RL::PlaySound(snd);
}
