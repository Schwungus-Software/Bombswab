#pragma once

#include <cstddef>
#include <exception>
#include <memory>
#include <variant>

class InvalidID : public std::exception {};

#define STRONG(data) (std::get<std::shared_ptr<T>>(data))
#define WEAK(data) (std::get<std::weak_ptr<T>>(data))

template <typename T>
class ID {
  private:
    bool owner_of_data;
    std::variant<std::shared_ptr<T>, std::weak_ptr<T>> data;

  public:
    ID(T* owned) : owner_of_data(true) {
        data = std::shared_ptr<T>(owned);
    }

    ID() : ID<T>(new T) {}

    template <typename... Args>
    ID(Args&&... constructor_args) : ID<T>(new T(std::forward<Args>(constructor_args)...)) {}

    ID(ID<T>& another) : ID<T>(const_cast<const ID<T>&>(another)) {}

    ID(const ID<T>& another) : owner_of_data(false) {
        if (another.owner_of_data) {
            std::weak_ptr<T> weak = STRONG(another.data);
            data = weak;
        } else {
            data = another.data;
        }
    }

    bool valid() const {
        return owner_of_data || !WEAK(data).expired();
    }

    void invalidate() {
        data = std::weak_ptr<T>();
        owner_of_data = false;
    }

    T* operator->() {
        return &operator*();
    }

    const T* operator->() const {
        return &operator*();
    }

    T& operator*() {
        if (!valid()) {
            throw InvalidID();
        }

        if (owner_of_data) {
            return *STRONG(data);
        } else {
            return *WEAK(data).lock();
        }
    }

    const T& operator*() const {
        if (!valid()) {
            throw InvalidID();
        }

        if (owner_of_data) {
            return *STRONG(data);
        } else {
            return *WEAK(data).lock();
        }
    }

    ~ID() = default;
};

#undef STRONG
#undef WEAK
