#pragma once

#include <exception>
#include <memory>

#include "id.tpp"

class Item;

class TakeFailed : public std::exception {};

class TakeFromEmptySlot : public TakeFailed {};
class TakeInvalidCast : public TakeFailed {};

struct ItemSlot {
  private:
    std::unique_ptr<Item> contents = nullptr;

  public:
    ItemSlot() = default;
    ItemSlot(Item* contents) : contents(contents) {}
    ~ItemSlot() = default;

    void tick();

    std::unique_ptr<Item> insert(Item*);

    template <typename T>
    T* take_as() {
        if (empty()) {
            throw TakeFromEmptySlot();
        }

        const auto cast = dynamic_cast<T*>(peek());

        if (cast == nullptr) {
            throw TakeInvalidCast();
        } else {
            const auto ptr = contents.release();
            return dynamic_cast<T*>(ptr);
        }
    }

    void trash();

    Item* take();

    bool empty() const {
        return peek() == nullptr;
    }

    Item* peek() const {
        return contents.get();
    }
};
