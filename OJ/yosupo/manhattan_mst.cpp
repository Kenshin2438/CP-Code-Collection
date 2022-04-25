#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

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

void SingleTest(int TestCase) {
  int n;
  cin >> n;
  vec<int> xs(n), ys(n);
  for (int i = 0; i < n; i++) {
    cin >> xs[i] >> ys[i];
  }
  auto [mst, P] = ManMST(xs, ys);
  cout << mst << '\n';
  for (auto [u, v] : P) {
    cout << u << ' ' << v << '\n';
  }
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
