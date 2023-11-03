#pragma once

#include "actions.hpp"
#include "items.hpp"
#include "rlwrap.hpp"
#include "things.hpp"

class AbstractWeapon : public Item {
  public:
    const int shoot_cooldown;
    int turns_until_ready;

    AbstractWeapon(int shoot_cooldown) : shoot_cooldown(shoot_cooldown) {}

    void tick() override {
        if (turns_until_ready > 0) {
            turns_until_ready--;
        }
    }

    virtual Projectile* shoot(RL::Vector2) = 0;
};

class BulletWeapon : public AbstractWeapon {
  public:
    const int range, damage;
    ItemSlot clip_slot;

    BulletWeapon(int range, int damage, int shoot_cooldown)
        : AbstractWeapon(shoot_cooldown), range(range), damage(damage) {}

    Projectile* shoot(RL::Vector2 destination) override;

    BulletClip* clip();

    Action* insert(Thing& actor, ItemSlot& source) override;
};

class Rifle : public BulletWeapon {
  public:
    Rifle() : BulletWeapon(20, 5, 8) {}

    std::string name() override {
        return "Rifle";
    }

    std::vector<Sprite> draw() override {
        return {ThingSprite::RIFLE};
    }
};

class Pistol : public BulletWeapon {
  public:
    Pistol() : BulletWeapon(10, 10, 40) {}

    std::string name() override {
        return "Pistol";
    }

    std::vector<Sprite> draw() override {
        return {ThingSprite::PISTOL};
    }
};
