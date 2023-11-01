#pragma once

#include "rlwrap.hpp"
#include "things.hpp"

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

class Die : public Action {
  public:
    Die() : Action(1) {}

    void perform(Thing&) override;
};

class Move : public Action {
  public:
    Direction dir;

    Move(Direction dir, int length) : Action(length), dir(dir) {}

    void perform(Thing&) override;
};

class Shoot : public Action {
  public:
    RL::Vector2 destination;
    HandSlot slot;

    Shoot(RL::Vector2 destination, HandSlot slot)
        : Action(1), destination(destination), slot(slot) {}

    void perform(Thing&) override;
};
