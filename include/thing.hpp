#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "audio.hpp"
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
    // Movement.

    int x, y;
    Direction dir;

    // Actions.

    std::unique_ptr<Action> ongoing;

    // Health.

    int max_health, cur_health;

    // Main flags.

    // Ignored in collision detection. This can still be bypassed.
    bool ghost;

    // Misc. flags.

    bool deletion_mark;
    bool stepped;

    Thing(int, int);

    void tick();

    /// Called every turn.
    virtual void think() {}

    /// Called every time an action can be taken.
    virtual void act() {}

    // Draw this thing in multiple layers.
    virtual std::vector<TintedSprite> draw() = 0;

    /// Deal damage and return `true` if it was fatal.
    bool damage(int);

    bool collides_with(const Thing&, bool = false);
    Thing* collide_at(bool = false);

    void play_sound(RL::Sound);
    void play_sound_local(RL::Sound);

    virtual void step() {}

    virtual void before_death() {}

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