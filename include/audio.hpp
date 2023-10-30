#pragma once

#include "rlwrap.hpp"

extern RL::Sound footstep1;
extern RL::Sound footstep2;
extern RL::Sound footstep3;
extern RL::Sound footstep4;
extern RL::Sound footstep5;
extern RL::Sound footstep6;
extern RL::Sound rifle_fire;
extern RL::Sound human_die;
extern RL::Sound explode1;
extern RL::Sound explode2;
extern RL::Sound explode3;

void load_sounds();

void play_sound_global(RL::Sound);
void play_sound_at(RL::Sound, RL::Vector2);
