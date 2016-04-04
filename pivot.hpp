/**
 * @file pivot.hpp
 * @brief header of Pivot class
 */

#pragma once

#include <list>

#include "graph.hpp"
#include "util.hpp"

namespace bk {
template <class V>
using Vertices = typename Graph<V>::Vertices;
template <class V>
using Cliques = std::list<Vertices<V>>;

class Pivot {
 private:
  template <class V>
  struct Report;

  template <class V>
  static auto _selectPivot(const Graph<V>& g, const Vertices<V>& p) -> V*;
  template <class V>
  static auto _getNeighbors(const Graph<V>& g, V* v) -> Vertices<V>;
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
  };
};

template <class V>
auto Pivot::_selectPivot(const Graph<V>& g, const Vertices<V>& p)
  -> V* {
  V* pivot;
  int max_neighbor_number = -1;
  for(const auto& v : p) {
    int neighbor_number = g.getAdjacentVertices(v).size();
    if(neighbor_number > max_neighbor_number) {
      max_neighbor_number = neighbor_number;
      pivot = v;
    }
  }
  return pivot;
}

template <class V>
inline auto Pivot::_getNeighbors(const Graph<V>& g, V* v)
  -> Vertices<V> {
  return std::move(g.getAdjacentVertices(v));
}

template <class V>
inline auto Pivot::_reportMaximalClique(Vertices<V>&& r) -> void {
  Report<V>::cliques.push_back(std::move(r));
}

template <class V>
auto Pivot::_solve(const Graph<V>& g,
                   Vertices<V>&& r,
                   Vertices<V>&& p,
                   Vertices<V>&& x) -> void {
  if(p.empty() && x.empty()) return _reportMaximalClique<V>(std::move(r));
  auto u = _getNeighbors(g, _selectPivot(g, p));
  for(const auto& v : util::set_difference(p, u)) {
    auto nv = _getNeighbors(g, v);
    _solve(set_union(r, v), set_intersection(p, nv), set_intersection(x, nv));
    p.erase(v);
    x.insert(v);
  }
}

template <class V>
auto Pivot::solve(const Graph<V>& g) -> Cliques<V> {
  Report<V>::cliques.clear();
  Vertices<V> r, p = g.getVertices(), x;
  _solve(g, std::move(r), std::move(p), std::move(x));
  return std::move(Report<V>::cliques);
}
}
