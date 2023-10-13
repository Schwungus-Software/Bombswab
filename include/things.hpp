#pragma once

#include "line.hpp"
#include "thing.hpp"

extern std::vector<std::unique_ptr<Thing>> things;
extern std::vector<std::unique_ptr<Thing>> spawn_queue;

class Player : public Thing {
  public:
    Player(int x, int y) : Thing(x, y) {}

    void think() override;
    std::vector<TintedSprite> draw() override;

    void step() override;
};

class Projectile : public Thing {
  public:
    int range;

    int dest_x, dest_y;

    std::vector<Point> trajectory;
    std::size_t cur_point;

    Projectile(int dest_x, int dest_y, int range)
        : Thing(0, 0), range(range), dest_x(dest_x), dest_y(dest_y),
          cur_point(0) {}

    void think() override;
};

class Bullet : public Projectile {
  public:
    Bullet(int dest_x, int dest_y) : Projectile(dest_x, dest_y, 30) {}

    std::vector<TintedSprite> draw() override;
};
