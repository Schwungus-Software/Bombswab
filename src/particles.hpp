#pragma once

#include "spritesheets.hpp"

struct ParticleInstance {
    Vector2 position;
    Particle index;
    int lifetime;
};
