#pragma once

#include "thing.hpp"

class Player : public Thing {
  public:
    Player(int, int);

    bool stepped;

    void think() override;
    std::vector<TintedSprite> draw() override;
    void step() override;
};
