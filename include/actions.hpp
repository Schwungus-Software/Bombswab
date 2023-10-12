#include "thing.hpp"

enum class Direction {
  LEFT,
  RIGHT,
  UP,
  DOWN,
};

class Move : public Action {
  public:
    Direction dir;

    Move(Direction dir, int length) : Action(length), dir(dir) {}

    void perform(Thing&) override;
};
