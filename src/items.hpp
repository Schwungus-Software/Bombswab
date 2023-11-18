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

    virtual std::string name() = 0;

    virtual std::vector<Sprite> draw() = 0;

    virtual void tick() {}

    virtual Action* activate(Thing& actor) {
        return nullptr;
    }

    virtual Action* insert(Thing& actor, ItemSlot& source) {
        return nullptr;
    }

    virtual ~Item();
};

class SimpleItem : public Item {
  public:
    std::string static_name;

  protected:
    SimpleItem(std::string name) : static_name(name) {}

  public:
    std::string name() override {
        return static_name;
    }
};

class BulletClip : public SimpleItem {
  public:
    std::size_t ammo_count;

    BulletClip(std::size_t ammo_count) : SimpleItem("Clip"), ammo_count(ammo_count) {}

    std::vector<Sprite> draw() override {
        return {ThingSprite::BULLET};
    }
};
