#include "../main.hpp"

struct DSU {
  vec<int> p;
  DSU(int _) : p(_ + 1) { iota(all(p), 0); }
  int f(int _) { return _ == p[_] ? _ : p[_] = f(p[_]); }
  bool same(int u, int v) { return f(u) == f(v); }
  bool unite(int u, int v) {
    u = f(u), v = f(v);
    if (u == v) return false;
    return p[u] = v, true;
  }
};
