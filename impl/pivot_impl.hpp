#pragma once

#include "../util.hpp"

namespace bk {
template <class V>
Cliques<V> Pivot::Report<V>::cliques;

template <class V>
auto Pivot::_selectPivot(const Graph<V>& g, const Vertices<V>& p) -> V {
  assert(!p.empty());

  V pivot = *p.begin();
  int max_neighbor_number = 0;
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
inline auto Pivot::_getNeighbors(const Graph<V>& g, V v) -> Vertices<V> {
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
  if(p.empty()) {
    if(x.empty()) _reportMaximalClique<V>(std::move(r));
    return;
  }
  auto u = _getNeighbors(g, _selectPivot(g, p));
  for(const auto& v : util::set_difference(p, u)) {
    auto nv = _getNeighbors(g, v);
    _solve(g,
           util::set_union(r, v),
           util::set_intersection(p, nv),
           util::set_intersection(x, nv));
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
