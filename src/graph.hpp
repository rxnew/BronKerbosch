/**
 * @file graph.hpp
 * @brief header of Graph class
 */

#pragma once

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
  auto getAdjacentVertices(V* v) -> const Vertices&;
  auto isEmpty() const -> bool;
  auto addVertice(V* v) -> void;
  auto removeVertice(V* v) -> void;
  auto removeVertice(const Vertices& vertices) -> void;
  template <class... Rest>
  auto addEdge(V* v, V* u, Rest... rest) -> void;
  template <class... Rest>
  auto removeEdge(V* v, V* u, Rest... rest) -> void;
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
  return *this->adjacency_list_.find(v);
}

template <class V>
inline auto Graph<V>::isEmpty() const -> bool {
  return this->vertices_.empty();
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
auto Graph<V>::removeVertice(const Vertices& vertices) -> void {
  for(const auto& v : vertices) {
    this->removeVertice(v);
  }
}

template <class V>
template <class... Rest>
auto auto Graph<V>::addEdge(V* v, V* u, Rest... rest)
  -> void {
  this->adjacency_list_[v].insert(u);
  this->adjacency_list_[u].insert(v);
  if(sizeof...(Rest)) this->addEdge(v, rest...);
}

template <class V>
template <class... Rest>
auto auto Graph<V>::removeEdge(V* v, V* u, Rest... rest) -> void {
  this->adjacency_list_[v].erase(u);
  this->adjacency_list_[u].erase(v);
  if(sizeof...(Rest)) this->removeEdge(v, rest...);
}

template <class V>
inline auto Graph<V>::existEdge(V* v, V* u) const -> bool {
  return this->adjacency_list_[v].count(u);
}
}
