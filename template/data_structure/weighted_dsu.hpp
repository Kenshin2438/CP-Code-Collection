#include "../main.hpp"

struct Weighted_DSU {
  vec<int> p, val;

  Weighted_DSU() {}
  Weighted_DSU(int n, int init = 0) : p(n), val(n, init) {
    iota(all(p), 0);
  }

  int find(int x) {
    if (x == p[x]) return x;
    int fa = find(p[x]);
    val[x] += val[p[x]];
    return p[x] = fa;
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
  int weight(int x) {
    return find(x), val[x];
  }
  int diff(int x, int y) { // query (a[y] - a[x])
    return weight(y) - weight(x);
  }
  bool unite(int x, int y, int dif = 0) {
  // add constraint (a[y] - a[x] = dif)
    dif = weight(y) - weight(x) - dif;
    x = find(x), y = find(y);
    if (x == y) return false;
    p[x] = y, val[x] = dif;
    return true;
  }
};