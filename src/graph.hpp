/**
 * @file graph.hpp
 * @brief header of Graph class
 */

#pragma once

namespace bk {
template <class V>
class Graph {
 public:
  using NodeSet = std::unordered_set<V*>;

 private:
  NodeSet nodes_;
  std::unordered_map<V*, VSet> adjacency_;

 public:
  Graph() = default;
  template <class T>
  explicit Graph(T&& adjacency);
  ~Graph() = default;
  auto addNode(V* node) -> void;
  template <class... Rest>
  auto addEdge(V* node1, V* node2, Rest... rest) -> void;
  template <class... Rest>
  auto removeEdge(V* node1, V* node2, Rest... rest) -> void;
  auto existEdge(V* node1, V* node2) -> bool;
};

template <class V>
template <class T>
inline Graph<V>::Graph(T&& adjacency)
  : adjacency_(std::forward<T>(adjacency)) {
}

template <class V>
inline Graph<V>::addNode(V* node) -> void {
  this->nodes_.insert(node);
}

template <class V>
template <class... Rest>
auto Graph<V>::addEdge(V* node1, V* node2, Rest... rest)
  -> void {
  this->adjacency_[node1].insert(node2);
  this->adjacency_[node2].insert(node1);
  if(sizeof...(Rest)) addEdge(node1, rest...);
}

template <class V>
template <class... Rest>
auto Graph<V>::removeEdge(V* node1, V* node2, Rest... rest)
  -> void {
  this->adjacency_[node1].erase(node2);
  this->adjacency_[node2].erase(node1);
  if(sizeof...(Rest)) removeEdge(node1, rest...);
}

template <class V>
inline auto Graph<V>::existEdge(V* node1, V* node2) -> bool {
  return this->adjacency_[node1].count(node2);
}
}
