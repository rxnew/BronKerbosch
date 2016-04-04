/**
 * @file graph.hpp
 * @brief header of Graph class
 */

#pragma once

#include <unordered_set>
#include <unordered_map>

namespace bk {
template <class V>
class Graph {
 public:
  using Vertices = std::unordered_set<V*>;
  using AdjacencyList = std::unordered_map<V*, Vertices>;

 private:
  Vertices vertices_;
  AdjacencyList adjacency_list_;

 public:
  Graph() = default;
  template <class T>
  explicit Graph(T&& vertices);
  Graph(const Graph&) = default;
  Graph(Graph&&) = default;
  ~Graph() = default;

  auto getVertices() const -> const Vertices&;
  auto getAdjacentVertices(V* v) const -> const Vertices&;
  auto addVertice(V* v) -> void;
  auto removeVertice(V* v) -> void;
  auto addEdge(V* v, V* u) -> void;
  auto removeEdge(V* v, V* u) -> void;
  auto existEdge(V* v, V* u) const -> bool;
};

template <class V>
template <class T>
inline Graph<V>::Graph(T&& vertices) : vertices_(std::forward<T>(vertices)) {
}

template <class V>
inline auto Graph<V>::getVertices() const -> const Vertices& {
  return this->vertices_;
}

template <class V>
inline auto Graph<V>::getAdjacentVertices(V* v) const -> const Vertices& {
  return this->adjacency_list_.find(v)->second;
}

template <class V>
inline auto Graph<V>::addVertice(V* v) -> void {
  this->vertices_.insert(v);
  this->adjacency_list_.insert(v);
}

template <class V>
auto Graph<V>::removeVertice(V* v) -> void {
  this->vertices_.erase(v);
  for(const auto& u : this->adjacency_list_[v]) {
    this->adjacency_list_[u].erase(v);
  }
  this->adjacency_list_.erase(v);
}

template <class V>
inline auto Graph<V>::addEdge(V* v, V* u) -> void {
  this->adjacency_list_[v].insert(u);
  this->adjacency_list_[u].insert(v);
}

template <class V>
inline auto Graph<V>::removeEdge(V* v, V* u) -> void {
  this->adjacency_list_[v].erase(u);
  this->adjacency_list_[u].erase(v);
}

template <class V>
inline auto Graph<V>::existEdge(V* v, V* u) const -> bool {
  return this->adjacency_list_[v].count(u);
}
}
