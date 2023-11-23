#include "item_slot.hpp"
#include "items.hpp"
#include "level.hpp"

void ItemSlot::tick() {
    if (contents != nullptr) {
        contents->tick();
    }
}

std::unique_ptr<Item> ItemSlot::insert(Item* another) {
    const auto tmp = contents.release();
    contents.reset(another);
    return std::unique_ptr<Item>(tmp);
}

void ItemSlot::trash() {
    // TODO: create a drop-on-the-ground version.
    try {
        delete take();
    } catch (const TakeFailed&) {}
}

Item* ItemSlot::take() {
    return take_as<Item>();
}
