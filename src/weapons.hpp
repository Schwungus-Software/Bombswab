#pragma once

#include "raylib.h"

#include "actions.hpp"
#include "items.hpp"
#include "things.hpp"

class AbstractWeapon : public Item {
  public:
    const int shoot_cooldown;
    int turns_until_ready;

    AbstractWeapon(int shoot_cooldown) : shoot_cooldown(shoot_cooldown) {
        name = "Weapon";
    }

    void tick() override {
        if (turns_until_ready > 0) {
            turns_until_ready--;
        }
    }

    virtual Projectile* shoot(Vector2) = 0;
};

class BulletWeapon : public AbstractWeapon {
  public:
    const int range, damage;
    ID<ItemSlot> clip_slot;

    BulletWeapon(int range, int damage, int shoot_cooldown)
        : AbstractWeapon(shoot_cooldown), range(range), damage(damage) {}

    Projectile* shoot(Vector2 destination) override;

    BulletClip* clip();

    Action* insert(Thing& actor, ID<ItemSlot> source) override;
};

class AssaultRifle : public BulletWeapon {
  public:
    AssaultRifle() : BulletWeapon(20, 5, 8) {
        name = "Assault rifle";
        sprite = {ThingSprite::RIFLE};
    }
};

class Pistol : public BulletWeapon {
  public:
    Pistol() : BulletWeapon(10, 10, 40) {
        name = "Pistol";
        sprite = {ThingSprite::PISTOL};
    }
};
