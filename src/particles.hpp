#pragma once

#include <cstdint>
#include <vector>

#include "spritesheets.hpp"

struct ParticleInstance {
    Vector2 position;
    Particle index;
    int lifetime;
};

extern std::vector<ParticleInstance> particles;

void tick_particles();
void draw_particles();

void spawn_particle(Vector2, Particle, int);
