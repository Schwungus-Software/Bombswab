#pragma once

#include "line.hpp"
#include "thing.hpp"

extern std::vector<std::unique_ptr<Thing>> things;
extern std::vector<std::unique_ptr<Thing>> spawn_queue;

class Player : public Thing {
  public:
    Player(int x, int y) : Thing(x, y) {}

    void act() override;
    std::vector<TintedSprite> draw() override;

    void step() override;
};

class Enemy : public Thing {
  public:
    Enemy(int x, int y) : Thing(x, y) {}

    void act() override;
    std::vector<TintedSprite> draw() override;

    // TODO: override `step`.

    void before_death() override;
};

class Corpse : public Thing {
  public:
    Corpse(int x, int y) : Thing(x, y) { ghost = true; }

    std::vector<TintedSprite> draw() override;

    // TODO: override `before_death` to add blood splatters.
};

class Projectile : public Thing {
  public:
    int range, damage;
    int dest_x, dest_y;

    std::vector<Point> trajectory;
    std::size_t cur_point;

    Projectile(int dest_x, int dest_y, int range, int damage)
        : Thing(0, 0), range(range), damage(damage), dest_x(dest_x),
          dest_y(dest_y), cur_point(0) {}

    void act() override;
};

class Bullet : public Projectile {
  public:
    Bullet(int dest_x, int dest_y) : Projectile(dest_x, dest_y, 30, 10) {}

    std::vector<TintedSprite> draw() override;
};
