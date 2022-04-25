#include "../main.hpp"
#include "../data_structure/disjoint_set_union.hpp"

tuple<ll, vec<PII>> ManMST(vec<int> xs, vec<int> ys) {
  vec<int> id(SZ(xs)); iota(all(id), 0);
  vec<tuple<ll, int, int>> edges;
  for (int s = 0; s < 2; s++) {
    for (int t = 0; t < 2; t++) {
      sort(all(id), [&](int i, int j) {
        return xs[i] + ys[i] < xs[j] + ys[j];
      });
      map<int, int> sweep;
      for (int i : id) {
        for (auto it = sweep.lower_bound(-ys[i]); it != sweep.end();
             it = sweep.erase(it)) {
          int j = it->se;
          if (xs[i] - xs[j] < ys[i] - ys[j]) break;
          int w = abs(xs[i] - xs[j]) + abs(ys[i] - ys[j]);
          edges.emplace_back(w, i, j);
        }
        sweep[-ys[i]] = i;
      }
      swap(xs, ys);
    }
    for (auto &x : xs) x = -x;
  }
  ll mst = 0;
  DSU dsu = DSU(SZ(xs));
  vec<PII> P;
  sort(all(edges));
  for (auto [w, u, v] : edges) {
    if (dsu.unite(u, v)) {
      mst += w, P.emplace_back(u, v);
    }
  }
  return {mst, P};
}
