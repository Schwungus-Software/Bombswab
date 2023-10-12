#pragma once

#include "thing.hpp"

extern std::vector<std::unique_ptr<Thing>> things;
extern std::vector<std::unique_ptr<Thing>> spawn_queue;

class Player : public Thing {
  public:
    Player(int x, int y) : Thing(x, y) {}

    void think() override;
    std::vector<TintedSprite> draw() override;
};

class Bullet : public Thing {
  public:
    int range;

    Bullet(int x, int y, int range) : Thing(x, y), range(range) {}

    void think() override;
    std::vector<TintedSprite> draw() override;
};
