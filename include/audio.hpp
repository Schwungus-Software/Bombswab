#pragma once

#include <array>

#include "rlwrap.hpp"

extern RL::Sound footstep1, footstep2, footstep3, footstep4, footstep5,
    footstep6, rifle_fire, human_die, explode1, explode2, explode3, pain1, pain2, pain3;

const std::array<const RL::Sound*, 6> footsteps{
    &footstep1, &footstep2, &footstep3, &footstep4, &footstep5, &footstep6};

const std::array<const RL::Sound*, 3> explosions{&explode1, &explode2,
                                                 &explode3};

const std::array<const RL::Sound*, 3> pains{&pain1, &pain2, &pain3};

void load_sounds();

void play_sound_global(const RL::Sound&);
void play_sound_at(const RL::Sound&, RL::Vector2);
