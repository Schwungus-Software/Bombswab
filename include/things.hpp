#pragma once

#include "thing.hpp"

class Player : public Thing {
  public:
    Player(int, int);

    void think() override;
    std::vector<Sprite> draw() override;
};
