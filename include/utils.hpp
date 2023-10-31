#pragma once

#include <array>

#include "rlwrap.hpp"

template <typename T, std::size_t C>
const T& pick(const std::array<T, C>& items) {
    const auto choice = RL::GetRandomValue(0, C - 1);
    return items[choice];
}
