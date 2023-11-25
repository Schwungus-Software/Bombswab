#pragma once

#include <memory>
#include <string>
#include <vector>

#include "actions.hpp"
#include "item_slot.hpp"
#include "spritesheets.hpp"

class Item {
  public:
    using Sprite = TintedSprite<ThingSprite>;

    std::string name;

    Item(const std::string& name) : name(name) {}

    virtual std::vector<Sprite> draw() = 0;

    virtual void tick() {}

    virtual Action* activate(Thing& actor) {
        return nullptr;
    }

    virtual Action* insert(Thing& actor, ID<ItemSlot> source) {
        return nullptr;
    }

    virtual ~Item();
};

class BulletClip : public Item {
  public:
    std::size_t ammo_count;

    BulletClip(std::size_t ammo_count) : Item("Clip"), ammo_count(ammo_count) {}

    std::vector<Sprite> draw() override {
        return {ThingSprite::BULLET};
    }
};
