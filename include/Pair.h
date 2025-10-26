#pragma once
#include <compare>

template <typename Key, typename Value>
struct Pair {
    Key first;
    Value second;
    Pair() = default;
    Pair(const Key& k, const Value& v) : first(k), second(v) {}
    auto operator<=>(const Pair&) const = default;
};
