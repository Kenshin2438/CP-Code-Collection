#include "../data_structure/disjoint_set_union.hpp"
#include "../main.hpp"

tuple<ll, vector<pair<int, int>>> ManMST(vector<int> xs, vector<int> ys) {
  vector<int> id(xs.size());
  iota(all(id), 0);
  vector<tuple<ll, int, int>> edges;
  for (int s = 0; s < 2; s++) {
    for (int t = 0; t < 2; t++) {
      sort(all(id),
           [&](int i, int j) { return xs[i] + ys[i] < xs[j] + ys[j]; });
      map<int, int> sweep;
      for (int i : id) {
        for (auto it = sweep.lower_bound(-ys[i]); it != sweep.end();
             it = sweep.erase(it)) {
          int j = it->second;
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
  DSU dsu = DSU(xs.size());
  vector<pair<int, int>> P;
  sort(all(edges));
  for (auto [w, u, v] : edges) {
    if (dsu.merge(u, v)) {
      mst += w, P.emplace_back(u, v);
    }
  }
  return {mst, P};
}
