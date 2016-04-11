/**
 * @file pivot.hpp
 * @brief header of Pivot class
 */

#pragma once

#include <list>

#include "graph.hpp"

namespace bk {
template <class V>
using Vertices = typename Graph<V>::Vertices;
template <class V>
using Cliques = std::list<Vertices<V>>;

class Pivot {
 private:
  template <class V>
  struct Report;

  Pivot() = delete;

  template <class V>
  static auto _selectPivot(const Graph<V>& g, const Vertices<V>& p) -> V;
  template <class V>
  static auto _getNeighbors(const Graph<V>& g, V v) -> Vertices<V>;
  template <class V>
  static auto _reportMaximalClique(Vertices<V>&& r) -> void;
  template <class V>
  static auto _solve(const Graph<V>& g,
                     Vertices<V>&& r,
                     Vertices<V>&& p,
                     Vertices<V>&& x) -> void;

 public:
  template <class V>
  static auto solve(const Graph<V>& g) -> Cliques<V>;

 private:
  template <class V>
  struct Report {
    static Cliques<V> cliques;
    Report() = delete;
  };
};
}

#include "impl/pivot.hpp"
