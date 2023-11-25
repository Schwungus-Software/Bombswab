#pragma once

#include "raylib.h"

#include "actions.hpp"
#include "items.hpp"
#include "things.hpp"

class AbstractWeapon : public Item {
  public:
    const int shoot_cooldown;
    int turns_until_ready;

    AbstractWeapon(const std::string& name, int shoot_cooldown) : Item(name), shoot_cooldown(shoot_cooldown) {}

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

    BulletWeapon(const std::string& name, int range, int damage, int shoot_cooldown)
        : AbstractWeapon(name, shoot_cooldown), range(range), damage(damage) {}

    Projectile* shoot(Vector2 destination) override;

    BulletClip* clip();

    Action* insert(Thing& actor, ID<ItemSlot> source) override;
};

class Rifle : public BulletWeapon {
  public:
    Rifle() : BulletWeapon("Rifle", 20, 5, 8) {}

    std::vector<Sprite> draw() override {
        return {ThingSprite::RIFLE};
    }
};

class Pistol : public BulletWeapon {
  public:
    Pistol() : BulletWeapon("Pistol", 10, 10, 40) {}

    std::vector<Sprite> draw() override {
        return {ThingSprite::PISTOL};
    }
};
