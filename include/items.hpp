#pragma once

#include <memory>
#include <string>
#include <vector>

#include "spritesheets.hpp"

class Thing;

struct ItemSlot;

class Item {
  public:
    using Sprite = TintedSprite<ThingSprite>;

    virtual std::string name() = 0;

    virtual std::vector<Sprite> draw() = 0;

    virtual void tick() {}

    virtual bool activate(Thing&) {
        return false;
    }

    virtual bool insert(Thing&, ItemSlot&) {
        return false;
    }

    virtual ~Item();
};

struct ItemSlot {
    std::unique_ptr<Item> contents;

    void tick() {
        if (contents != nullptr) {
            contents->tick();
        }
    }
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
