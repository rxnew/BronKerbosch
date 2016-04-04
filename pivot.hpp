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

  Pivot() = delete;

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
    Report() = delete;
  };
};

template <class V>
Cliques<V> Pivot::Report<V>::cliques = Cliques<V>();

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

template <class T>
auto print(const T& x) -> void {
  for(auto y : x)
    std::cout << *y;
  std::cout << std::endl;
}

template <class V>
auto Pivot::_solve(const Graph<V>& g,
                   Vertices<V>&& r,
                   Vertices<V>&& p,
                   Vertices<V>&& x) -> void {
  if(p.empty() && x.empty()) {
    std::cout << "Report: ";
    print(r);
    std::cout << std::endl;
    return _reportMaximalClique<V>(std::move(r));
  }
  if(p.empty()) return;
  auto u = _getNeighbors(g, _selectPivot(g, p));
  for(const auto& v : util::set_difference(p, u)) {
    auto nv = _getNeighbors(g, v);
    std::cout << "R: ";
    print(r);
    std::cout << "P: ";
    print(p);
    std::cout << "X: ";
    print(x);
    std::cout << "NV: ";
    print(nv);
    std::cout << "P union NV: ";
    print(util::set_union(p, nv));
    std::cout << "P intersect NV: ";
    print(util::set_intersection(p, nv));
    std::cout << "P difference NV: ";
    print(util::set_difference(p, nv));
    std::cout << std::endl;
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
