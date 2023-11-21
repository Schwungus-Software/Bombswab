#include "level.hpp"
#include "spritesheet.tpp"

Level level;

Level::~Level() {
    for (const auto ptr : spawn_queue) {
        delete ptr;
    }

    spawn_queue.clear();
}

void Level::spawn_thing(Thing* thing) {
    spawn_queue.push_back(thing);
}

void Level::spawn_particle(Vector2 pos, Particle index, int lifetime) {
    particles.push_back({pos, index, lifetime});
}

void Level::tick() {
    for (const auto& thing : things) {
        thing->tick();
    }

    grid.tick();

    // TODO: revise when the time comes.
    while (!spawn_queue.empty()) {
        things.push_back(std::unique_ptr<Thing>(spawn_queue.back()));
        spawn_queue.pop_back();
    }

    std::erase_if(things, [](const auto& thing) { return thing->deletion_mark; });

    std::erase_if(particles, [](auto& p) { return --p.lifetime <= 0; });
}

void Level::draw() {
    for (std::size_t i = 0; i < GRID_SIZE; i++) {
        const auto& tile = grid.tiles[i];

        const auto x = static_cast<float>(i % GRID_WIDTH);
        const auto y = static_cast<float>(i / GRID_HEIGHT);

        const auto sprite = tile.is_closed() ? Tile::CLOSED : tile.kind;
        ::draw<Tile>(sprite, {x, y});
    }

    for (const auto& thing : things) {
        const auto& tile_at = grid.tile_at(thing->pos());

        if (tile_at.is_closed()) {
            continue;
        }

        const auto layers = thing->draw();

        for (const auto& layer : layers) {
            ::draw<ThingSprite>(layer, thing->pos());
        }
    }

    for (const auto& particle : particles) {
        ::draw<Particle>(particle.index, particle.position);
    }
}
