#include "particles.hpp"

std::vector<ParticleInstance> particles;

void spawn_particle(Vector2 pos, Particle index, int lifetime) {
    particles.push_back({pos, index, lifetime});
}

void tick_particles() {
    std::erase_if(particles, [](auto& p) { return --p.lifetime <= 0; });
}

void draw_particles() {
    for (const auto& particle : particles) {
        draw<Particle>(particle.index, particle.position);
    }
}
