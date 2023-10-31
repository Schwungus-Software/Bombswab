#include "actions.hpp"
#include "grid.hpp"
#include "things.hpp"
#include "utils.hpp"

std::vector<Thing::Sprite> Humanoid::draw() {
    // TODO: flip correctly when going up/down too.
    const auto gun =
        dir == Direction::LEFT ? -ThingSprite::GUN : ThingSprite::GUN;
    return {{ThingSprite::MAN, body_color}, {gun}};
}

void Humanoid::step() {
    if (can_reveal_tiles) {
        grid.open(pos());
    }

    stepped = !stepped;

    if (stepped) {
        const auto footstep = pick(footsteps);
        play_sound_local(*footstep);
    }
}

void Humanoid::collide() {
    const auto& tile = grid.tile_at(pos());

    if (can_reveal_tiles) {
        grid.open(pos());
    }

    switch (dir) {
        case Direction::LEFT:
            x++;
            break;
        case Direction::RIGHT:
            x--;
            break;
        case Direction::UP:
            y++;
            break;
        case Direction::DOWN:
            y--;
            break;
    }
}

void Humanoid::before_death() {
    play_sound_local(human_die);

    auto corpse = std::make_unique<Corpse>(x, y);

    corpse->max_health = max_health;
    corpse->cur_health = std::max(1, max_health / 2);
    spawn_queue.push_back(std::move(corpse));
}

void Player::act() {
    const int movement_length = 8;

    if (RL::IsMouseButtonPressed(RL::MOUSE_BUTTON_LEFT)) {
        const auto dir = mouse_to_grid();

        ongoing.reset(new Shoot(new Bullet(dir.x, dir.y)));
    } else if (RL::IsKeyDown(RL::KEY_LEFT)) {
        ongoing.reset(new Move(Direction::LEFT, movement_length));
    } else if (RL::IsKeyDown(RL::KEY_RIGHT)) {
        ongoing.reset(new Move(Direction::RIGHT, movement_length));
    } else if (RL::IsKeyDown(RL::KEY_UP)) {
        ongoing.reset(new Move(Direction::UP, movement_length));
    } else if (RL::IsKeyDown(RL::KEY_DOWN)) {
        ongoing.reset(new Move(Direction::DOWN, movement_length));
    }
}

void Enemy::act() {
    // TODO: add AI.
}
