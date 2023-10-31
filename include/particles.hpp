#pragma once

#include <vector>

#include "spritesheet.hpp"

enum Particle {
    EXPLOSION = 1,
};

struct ParticleInstance {
    RL::Vector2 position;
    Particle index;
    int lifetime;
};

extern std::vector<ParticleInstance> particles;

void tick_particles();
void draw_particles();

void spawn_particle(RL::Vector2, Particle, int);
