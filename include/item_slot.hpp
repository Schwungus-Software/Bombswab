#pragma once

#include <memory>

class Item;

struct ItemSlot {
    std::unique_ptr<Item> contents;

    void tick();

    template <typename T>
    T* take_as() {
        const auto cast = dynamic_cast<T*>(contents.get());

        if (cast == nullptr) {
            return nullptr;
        } else {
            return dynamic_cast<T*>(contents.release());
        }
    }
};
