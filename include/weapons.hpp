#pragma once

#include "actions.hpp"
#include "rlwrap.hpp"
#include "things.hpp"

class AbstractWeapon {
  public:
    const int shoot_cooldown;
    int turns_until_ready;

    AbstractWeapon(int shoot_cooldown) : shoot_cooldown(shoot_cooldown) {}

    virtual Projectile* spawn_projectile(RL::Vector2) = 0;

    virtual ~AbstractWeapon();
};

class BulletWeapon : public AbstractWeapon {
  public:
    const int range, damage;

    BulletWeapon(int range, int damage, int shoot_cooldown)
        : AbstractWeapon(shoot_cooldown), range(range), damage(damage) {}

    Projectile* spawn_projectile(RL::Vector2 destination);
};

extern BulletWeapon rifle;
