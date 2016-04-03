/**
 * @file node.hpp
 * @brief header of Node class
 */

#pragma once

#include <unordered_set>

namespace bk {
template <class T>
class Node {
 public:
  using NodeSet = std::unordered_set<Node*>;

 private:
  T value_;
  NodeSet adjacency_;

 public:
  explicit Node(const T& value);
  template <class S>
  Node(const T& value, S&& adjacency);
  Node(const Node&) = default;
  Node(Node&&) noexcept = default;
  ~Node() = default;
  auto setValue(const T& value) -> void;
  template <class S>
  auto setAdjacency(S&& adjacency) -> void;
  auto addAdjacentNode(Node* node) -> void;

  friend class Graph;
};

template <class T>
inline Node<T>::Node(const T& value) : value_(value) {
}

template <class T>
template <class U>
inline Node<T>::Node(const T& value, S&& adjacency)
  : value_(value), adjacency_(std::forward<S>(adjacency)) {
}

template <class T>
inline auto Node<T>::setValue(const T& value) -> void {
  this->value_ = value;
}

template <class T>
template <class S>
inline auto Node<T>::setAdjacency(S&& adjacency) -> void {
  this->adjacency_ = std::forward<S>(adjacency);
}

template <class T>
inline auto Node<T>::addAdjacentNode(Node* node) -> void {
  this->adjacency_.insert(node);
}
}
