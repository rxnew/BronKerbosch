/**
 * @file graph.hpp
 * @brief header of Graph class
 */

#pragma once

namespace bk {
template <class V>
class Graph {
 public:
  using Vertices = std::unordered_set<V*>;
  using AdjacencyList = std::unordered_map<V*, Vertices>;

 private:
  Vertices vertices_;
  AdjacencyList adjacency_;

 public:
  Graph() = default;
  template <class T>
  explicit Graph(T&& adjacency);
  ~Graph() = default;
  auto addVertice(V* v) -> void;
  template <class... Rest>
  auto addEdge(V* v1, V* v2, Rest... rest) -> void;
  template <class... Rest>
  auto removeEdge(V* v1, V* v2, Rest... rest) -> void;
  auto existEdge(V* v1, V* v2) -> bool;
};

template <class V>
template <class T>
inline Graph<V>::Graph(T&& adjacency)
  : adjacency_(std::forward<T>(adjacency)) {
}

template <class V>
inline Graph<V>::addVertice(V* v) -> void {
  this->vertices_.insert(v);
}

template <class V>
template <class... Rest>
auto Graph<V>::addEdge(V* v1, V* v2, Rest... rest)
  -> void {
  this->adjacency_[v1].insert(v2);
  this->adjacency_[v2].insert(v1);
  if(sizeof...(Rest)) addEdge(v1, rest...);
}

template <class V>
template <class... Rest>
auto Graph<V>::removeEdge(V* v1, V* v2, Rest... rest)
  -> void {
  this->adjacency_[v1].erase(v2);
  this->adjacency_[v2].erase(v1);
  if(sizeof...(Rest)) removeEdge(v1, rest...);
}

template <class V>
inline auto Graph<V>::existEdge(V* v1, V* v2) -> bool {
  return this->adjacency_[v1].count(v2);
}
}
