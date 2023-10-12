#pragma once

#include <memory>
#include <vector>

#include "spritesheet.hpp"

class Action;

class Thing {
  public:
    int x, y;
    std::unique_ptr<Action> ongoing;

    Thing(int, int);

    void tick();

    virtual void think() = 0;
    virtual std::vector<Sprite> draw() = 0;

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
