/**
 * @file bron_kerbosch_pivot.hpp
 * @brief header of BronKerboschPivot class
 */

#pragma once

#include <list>

#include "graph.hpp"
#include "util.hpp"

namespace bk {
template <class V>
using Cliques = std::list<Graph<V>::Vertices>;

class BronKerboschPivot {
 private:
  template <class V>
  struct Report;

  template <class V, Vertices = Graph<V>::Vertices>
  static auto _selectPivot(const Graph<V>& g, const Vertices& p) -> V*;
  template <class V, Vertices = Graph<V>::Vertices>
  static auto _getNeighbors(const Graph<V>& g, V* v) -> Vertices;
  template <class V, Vertices = Graph<V>::Vertices>
  static auto _reportMaximalClique(Vertices&& r) -> void;
  template <class V, Vertices = Graph<V>::Vertices>
  static auto _solve(const Graph<V>& g, Vertices r, Vertices p, Vertices x)
    -> void;

 public:
  template <class V, Vertices = Graph<V>::Vertices>
  static auto solve(const Graph<V>& g) -> Cliques<V>;

 private:
  template <class V>
  struct Report {
    static Cliques<V> cliques;
  };
};

template <class V, Vertices = Graph<V>::Vertices>
auto BronKerboschPivot::_selectPivot(const Graph<V>& g, const Vertices& p)
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

template <class V, Vertices = Graph<V>::Vertices>
inline auto BronKerboschPivot::_getNeighbors(const Graph<V>& g, V* v)
  -> Vertices {
  return std::move(g.getAdjacentVertices(v));
}

template <class V, Vertices = Graph<V>::Vertices>
inline auto BronKerboschPivot::_reportMaximalClique(Vertices&& r) -> void {
  Report<V>::cliques.push_back(std::move(r));
}

template <class V, Vertices = Graph<V>::Vertices>
auto BronKerboschPivot::_solve(const Graph<V>& g,
                               Vertices&& r,
                               Vertices&& p,
                               Vertices&& x) -> void {
  if(p.isEmpty() && x.isEmpty()) return _reportMaximalClique(std::move(r));
  auto u = _getNeighbors(g, _selectPivot(g, p));
  for(const auto& v : util::set_difference(p, u)) {
    auto nv = _getNeighbors(g, v);
    _solve(set_union(r, v), set_intersection(p, nv), set_intersection(x, nv));
    p.erase(v);
    x.insert(v);
  }
}

template <class V, Vertices = Graph<V>::Vertices>
auto BronKerboschPivot::solve(const Graph<V>& g) -> Cliques<V> {
  Report<V>::cliques.clear();
  Vertices r, p = g.getVertices(), x;
  _solve(std::move(r), std::move(p), std::move(x));
  return std::move(Report<V>::cliques);
}
}
