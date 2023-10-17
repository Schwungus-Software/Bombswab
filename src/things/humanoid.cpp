#include "actions.hpp"
#include "grid.hpp"
#include "things.hpp"

std::vector<TintedSprite> Humanoid::draw() {
    // TODO: flip correctly when going up/down too.
    const auto gun = dir == Direction::LEFT ? -Sprite::GUN : Sprite::GUN;
    return {{Sprite::MAN, body_color}, gun};
}

void Humanoid::step() {
    RL::Sound footstep = {0};

    switch (RL::GetRandomValue(0, 5)) {
        case 0:
            footstep = footstep1;
            break;

        case 1:
            footstep = footstep2;
            break;

        case 2:
            footstep = footstep3;
            break;

        case 3:
            footstep = footstep4;
            break;

        case 4:
            footstep = footstep5;
            break;

        case 5:
            footstep = footstep6;
            break;
    }

    stepped = !stepped;

    if (stepped) {
        play_sound_local(footstep);
    }
}

void Humanoid::before_death() {
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
