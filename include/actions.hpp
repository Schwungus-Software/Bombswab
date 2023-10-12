#include "thing.hpp"

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
    int x, y;
    std::unique_ptr<Thing> projectile;

    Shoot(int x, int y, Thing* projectile)
        : Action(1), x(x), y(y), projectile(projectile) {}

    void perform(Thing&) override;
};
