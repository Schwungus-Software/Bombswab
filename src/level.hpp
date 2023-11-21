#pragma once

#include "grid.hpp"
#include "particles.hpp"
#include "things.hpp"

extern struct Level {
  public:
    Grid grid;
    std::vector<std::unique_ptr<Thing>> things;
    std::vector<ParticleInstance> particles;

  private:
    std::vector<Thing*> spawn_queue;

  public:
    Level() = default;
    ~Level();

    void spawn_thing(Thing*);
    void spawn_particle(Vector2, Particle, int);

    void tick();
    void draw();
} level;
