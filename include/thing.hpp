#pragma once

#include <memory>
#include <vector>

#include "spritesheet.hpp"

enum class Direction {
  LEFT,
  RIGHT,
  UP,
  DOWN,
};

class Action;

class Thing {
  public:
    int x, y;
    Direction dir;
    std::unique_ptr<Action> ongoing;

    bool deletion_mark;

    Thing(int, int);

    void tick();

    virtual void think() = 0;
    virtual std::vector<TintedSprite> draw() = 0;

    virtual ~Thing() = default;
};

class Action {
  public:
    int length;

    Action(int length) : length(length) {}

    virtual void perform(Thing&) = 0;
    void tick(Thing&);
    virtual ~Action() {}
};

class Noop : public Action {
  public:
    Noop() : Action(1) {}
    void perform(Thing&) override {}
};
