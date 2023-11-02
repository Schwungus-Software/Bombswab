#pragma once

#include <memory>

class Item;

struct ItemSlot {
    std::unique_ptr<Item> contents;

    void tick();
};
