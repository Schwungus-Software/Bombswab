#pragma once

#include <functional>
#include <variant>
#include <vector>

#include "raylib.h"

#include "actions.hpp"
#include "things.hpp"

struct Press {
    KeyboardKey key;

    Press(KeyboardKey key) : key(key) {}
};

struct Repeat {
    KeyboardKey key;

    Repeat(KeyboardKey key) : key(key) {}
};

struct Click {
    MouseButton button;

    Click(MouseButton button) : button(button) {}
};

struct Hold {
    MouseButton button;

    Hold(MouseButton button) : button(button) {}
};

struct Bind {
    using Kind = std::variant<Press, Repeat, Click, Hold>;
    Kind kind;

    Bind(const Press& kind) : kind(kind) {}
    Bind(const Repeat& kind) : kind(kind) {}
    Bind(const Click& kind) : kind(kind) {}
    Bind(const Hold& kind) : kind(kind) {}

    bool is_active() const;
};

struct Fallthrough {};
struct Finished {};

struct Binding {
    using Condition = std::function<bool(const Thing&)>;

    using Result = std::variant<Finished, Fallthrough>;
    using Action = std::function<Result(Thing&)>;

    Bind bind;
    Condition condition;
    Action action;

    Binding(Bind bind, Action action, Condition condition) : bind(bind), condition(condition), action(action) {}
    Binding(Bind bind, Action action) : Binding(bind, action, [](const auto&) { return true; }) {}
};

const extern std::vector<Binding> keybinds;
