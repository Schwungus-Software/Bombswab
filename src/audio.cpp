#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "audio.hpp"
#include "camera.hpp"
#include "grid.hpp"

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

void play_sound_at(const Sound& snd, Vector2 pos) {
    const auto listener = Vector2Scale(camera_center, 1.0 / SPRITE_DIM); // TODO: desync listener and camera_center
    const float init_dist = Vector2Distance(listener, pos);

    const float quiet_dist = 8.0; // can't hear jackshit from further
    const float loud_dist = 1.0;  // max volume achieved here
    const float range = quiet_dist - loud_dist;

    const float x = Clamp(init_dist - loud_dist, 0.0f, range);
    const float volume = 1.0 - std::pow(x / range, 2.0f); // TODO: square manually

    const float source_angle = std::atan2(pos.y - listener.y, pos.x - listener.x);
    const float x_dir = std::cos(source_angle);

    const float base_pan = init_dist < 0.5 ? 0.5 : 0.5 - x_dir / 2.0;
    const float shrink = 0.4;
    const float pan = 0.5 + shrink * (base_pan - 0.5);

    const Sound copy = snd;
    SetSoundPan(copy, pan);
    SetSoundVolume(copy, volume);

    PlaySound(copy);
}
