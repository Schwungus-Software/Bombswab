#include "thing.hpp"

class Move : public Action {
  public:
    Direction dir;

    Move(Direction dir, int length) : Action(length), dir(dir) {}

    void perform(Thing&) override;
};
