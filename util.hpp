/**
 * @file util.hpp
 * @brief header of Utilities
 */

#pragma once

#include <unordered_set>

namespace bk {
namespace util {
template <class T>
auto set_union(const std::unordered_set<T>& set, const T& value)
  -> std::unordered_set<T>;

template <class T>
auto set_union(const std::unordered_set<T>& lhs,
               const std::unordered_set<T>& rhs)
  -> std::unordered_set<T>;

template <class T>
auto set_intersection(const std::unordered_set<T>& lhs,
                      const std::unordered_set<T>& rhs)
  -> std::unordered_set<T>;

template <class T>
auto set_difference(const std::unordered_set<T>& lhs,
                    const std::unordered_set<T>& rhs)
  -> std::unordered_set<T>;
}
}

#include "impl/util_impl.hpp"
