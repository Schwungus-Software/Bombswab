#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "raylib.h"

class GameState;

struct Exit {
    std::string reason;
    bool success;
};

extern struct GSM {
  private:
    std::vector<std::unique_ptr<GameState>> stack;

  public:
    struct Push {
        GameState* next;
    };

    struct Pop {};

    struct Replace {
        GameState* next;
    };

    struct Ignore {};

    using Transition = std::variant<Ignore, Push, Pop, Replace>;

    GSM() = delete;

    GSM(GameState* initial) {
        stack.push_back(std::unique_ptr<GameState>(initial));
    }

    ~GSM() = default;

    void tick();
} gsm;

class GameState {
  public:
    virtual GSM::Transition tick() = 0;

    virtual ~GameState() = default;
};

class PickLocation : public GameState {
  private:
    Vector2 grid_pos;

  public:
    PickLocation();

    GSM::Transition tick() override;
};

class Play : public GameState {
  public:
    Play() = default;

    GSM::Transition tick() override;
};
