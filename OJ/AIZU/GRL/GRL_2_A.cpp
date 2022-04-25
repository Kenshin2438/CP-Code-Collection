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
#define all(a) a.begin(), a.end()
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

int n, m;
vec<tuple<int, int, int>> Edges;

void SingleTest(int TestCase) {
  cin >> n >> m;
  for (int u, v, d; m--; ) {
    cin >> u >> v >> d;
    Edges.emplace_back(d, u, v);
  }
  sort(all(Edges));
  DSU s(n);
  int ans = 0, cnt = 0;
  for (auto [d, u, v] : Edges) {
    if (s.unite(u, v)) ans += d, cnt++;
    if (cnt == n - 1) break;
  }
  cout << ans << '\n';
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
