/**
 * @file util.hpp
 * @brief header of Utilities
 */

#pragma once

#include <unordered_set>
#include <algorithm>

namespace bk {
namespace util {
template <class T>
auto set_union(const std::unordered_set<T>& set, const T& value)
  -> std::unordered_set<T>;

template <class T, class F>
auto set_operation(const std::unordered_set<T>& lhs,
                   const std::unordered_set<T>& rhs,
                   const F& operation) -> std::unordered_set<T>;

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

template <class T>
auto set_union(const std::unordered_set<T>& set, const T& value)
  -> std::unordered_set<T> {
  std::unordered_set<T> result = set;
  result.insert(value);
  return std::move(result);
}

template <class T, class F>
auto set_operation(const std::unordered_set<T>& lhs,
                   const std::unordered_set<T>& rhs,
                   const F& operation) -> std::unordered_set<T> {
  std::unordered_set<T> result;
  operation(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
            std::inserter(result, result.end()));
  return std::move(result);
}

template <class T>
inline auto set_union(const std::unordered_set<T>& lhs,
                      const std::unordered_set<T>& rhs)
  -> std::unordered_set<T> {
  return std::move(set_operation(lhs, rhs, std::set_union));
}

template <class T>
inline auto set_intersection(const std::unordered_set<T>& lhs,
                             const std::unordered_set<T>& rhs)
  -> std::unordered_set<T> {
  return std::move(set_operation(lhs, rhs, std::set_intersection));
}

template <class T>
inline auto set_difference(const std::unordered_set<T>& lhs,
                           const std::unordered_set<T>& rhs)
  -> std::unordered_set<T> {
  return std::move(set_operation(lhs, rhs, std::set_difference));
}
}
}
