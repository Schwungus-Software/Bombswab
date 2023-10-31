#include "particles.hpp"

template <>
const Spritesheet<Particle> spritesheet_for<Particle>{
    1, 1, "assets/particle_sheet.png"};

std::vector<ParticleInstance> particles;

void spawn_particle(RL::Vector2 pos, Particle index, int lifetime) {
    particles.push_back({pos, index, lifetime});
}

void tick_particles() {
    for (auto& particle : particles) {
        particle.lifetime--;
    }

    std::erase_if(particles, [](const auto& p) { return p.lifetime <= 0; });
}

void draw_particles() {
    for (const auto& particle : particles) {
        draw<Particle>(particle.index, particle.position);
    }
}
