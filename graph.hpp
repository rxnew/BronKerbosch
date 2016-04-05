/**
 * @file graph.hpp
 * @brief header of Graph class
 */

#pragma once

#include <unordered_set>
#include <unordered_map>
#include <cassert>

namespace bk {
template <class V>
class Graph {
 public:
  using Vertices = std::unordered_set<V>;
  using AdjacencyList = std::unordered_map<V, Vertices>;

 private:
  Vertices vertices_;
  AdjacencyList adjacency_list_;

  auto _initAdjacencyList() -> void;

 public:
  Graph() = default;
  Graph(size_t size);
  explicit Graph(const Vertices& vertices);
  explicit Graph(Vertices&& vertices);
  Graph(const Graph&) = default;
  Graph(Graph&&) = default;
  ~Graph() = default;

  auto getVertices() const -> const Vertices&;
  auto getAdjacentVertices(V v) const -> const Vertices&;
  auto addVertex(V v) -> void;
  auto removeVertex(V v) -> void;
  auto addEdge(V v, V u) -> void;
  auto removeEdge(V v, V u) -> void;
  auto existEdge(V v, V u) const -> bool;
};

template <class V>
auto Graph<V>::_initAdjacencyList() -> void {
  for(const auto& v : this->vertices_) {
    this->adjacency_list_.emplace(v, Vertices());
  }
}

template <class V>
inline Graph<V>::Graph(size_t size) : vertices_(size), adjacency_list_(size) {
}

template <class V>
inline Graph<V>::Graph(const Vertices& vertices)
  : vertices_(vertices), adjacency_list_(vertices.size()) {
  this->_initAdjacencyList();
}

template <class V>
inline Graph<V>::Graph(Vertices&& vertices)
  : vertices_(std::move(vertices)), adjacency_list_(vertices.size()) {
  this->_initAdjacencyList();
}

template <class V>
inline auto Graph<V>::getVertices() const -> const Vertices& {
  return this->vertices_;
}

template <class V>
inline auto Graph<V>::getAdjacentVertices(V v) const -> const Vertices& {
  auto pos = this->adjacency_list_.find(v);
  assert(pos != this->adjacency_list_.cend());
  return pos->second;
}

template <class V>
inline auto Graph<V>::addVertex(V v) -> void {
  this->vertices_.insert(v);
  this->adjacency_list_.emplace(v, Vertices());
}

template <class V>
auto Graph<V>::removeVertex(V v) -> void {
  this->vertices_.erase(v);
  for(const auto& u : this->adjacency_list_[v]) {
    this->adjacency_list_[u].erase(v);
  }
  this->adjacency_list_.erase(v);
}

template <class V>
inline auto Graph<V>::addEdge(V v, V u) -> void {
  this->adjacency_list_[v].insert(u);
  this->adjacency_list_[u].insert(v);
}

template <class V>
inline auto Graph<V>::removeEdge(V v, V u) -> void {
  this->adjacency_list_[v].erase(u);
  this->adjacency_list_[u].erase(v);
}

template <class V>
inline auto Graph<V>::existEdge(V v, V u) const -> bool {
  return this->adjacency_list_[v].count(u);
}
}
