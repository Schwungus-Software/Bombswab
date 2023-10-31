#pragma once

#include "line.hpp"
#include "thing.hpp"

extern std::vector<std::unique_ptr<Thing>> things;
extern std::vector<std::unique_ptr<Thing>> spawn_queue;

class Humanoid : public Thing {
  public:
    RL::Color body_color;

  protected:
    bool can_reveal_tiles;

  public:
    Humanoid(int x, int y, RL::Color body_color, bool can_reveal_tiles)
        : Thing(x, y), body_color(body_color),
          can_reveal_tiles(can_reveal_tiles) {}

    std::vector<Sprite> draw() override;

    void step() override;

    void collide() override;

    void before_death() override;
};

class Player : public Humanoid {
  public:
    Player(int x, int y) : Humanoid(x, y, RL::BLUE, true) {}

    void act() override;
};

class Enemy : public Humanoid {
  public:
    Enemy(int x, int y) : Humanoid(x, y, RL::RED, false) {}

    void act() override;
};

class Corpse : public Thing {
  public:
    Corpse(int x, int y) : Thing(x, y) { ghost = true; }

    std::vector<Sprite> draw() override;

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

    std::vector<Sprite> draw() override;
};
