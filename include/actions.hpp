#include "things.hpp"

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
    std::unique_ptr<Projectile> projectile;

    Shoot(Projectile* projectile) : Action(1), projectile(projectile) {}

    void perform(Thing&) override;
};
