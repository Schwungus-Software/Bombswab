#include "item_slot.hpp"
#include "items.hpp"

void ItemSlot::tick() {
    if (contents != nullptr) {
        contents->tick();
    }
}
