#include "audio.hpp"

Sound footstep1, footstep2, footstep3, footstep4, footstep5, footstep6, rifle_fire, human_die, explode1, explode2,
    explode3, pain1, pain2, pain3;

void load_sounds() {
    static bool ready = false;

    if (ready) {
        return;
    }

    footstep1 = LoadSound("assets/sounds/footstep1.wav");
    footstep2 = LoadSound("assets/sounds/footstep2.wav");
    footstep3 = LoadSound("assets/sounds/footstep3.wav");
    footstep4 = LoadSound("assets/sounds/footstep4.wav");
    footstep5 = LoadSound("assets/sounds/footstep5.wav");
    footstep6 = LoadSound("assets/sounds/footstep6.wav");
    rifle_fire = LoadSound("assets/sounds/rifle_fire.wav");
    human_die = LoadSound("assets/sounds/human_die.wav");
    explode1 = LoadSound("assets/sounds/explode1.wav");
    explode2 = LoadSound("assets/sounds/explode2.wav");
    explode3 = LoadSound("assets/sounds/explode3.wav");
    pain1 = LoadSound("assets/sounds/pain1.wav");
    pain2 = LoadSound("assets/sounds/pain2.wav");
    pain3 = LoadSound("assets/sounds/pain3.wav");

    ready = true;
}

void play_sound_global(const Sound& snd) {
    PlaySound(snd);
}

void play_sound_at(const Sound& snd, Vector2) {
    // TODO: implement with panning.
    PlaySound(snd);
}
