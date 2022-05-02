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

class LowLink {
private:
  vec<int> articulation_points;
  vec<PII> bridges;

  int n, m, idx;
  vec<vec<int>> G;
  vec<int> dfn, low;

  void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++idx;
    int cnt = 0, ok = 0;
    for (int v : G[u]) {
      if (dfn[v] == 0) {
        cnt++, tarjan(v, u);
        low[u] = min(low[u], low[v]);
        if (fa != -1 && dfn[u] <= low[v]) ok = 1;
        if (dfn[u] < low[v]) {
          bridges.push_back(minmax(v, u));
        }
      } else if (dfn[v] < dfn[u] && v != fa) {
        low[u] = min(low[u], dfn[v]);
      }
    }
    if (ok || (fa == -1 && cnt > 1)) {
      articulation_points.push_back(u);
    }
  }

public:
  LowLink(int _n, int _m) : n(_n), m(_m), G(n) {
    for (int u, v, _ = 0; _ < m; _++) {
      cin >> u >> v;
      G[u].emplace_back(v);
      G[v].emplace_back(u);
    }
  }
  pair<vec<int>, vec<PII>> low_link() {
    dfn.assign(n, 0);
    low.assign(n, 0);
    articulation_points.clear();
    bridges.clear();
    idx = 0; // init
    for (int i = 0; i < n; i++) {
      if (dfn[i] == 0) tarjan(i, -1);
    }
    return {articulation_points, bridges};
  }
};

void SingleTest(int TestCase) {
  int n, m; cin >> n >> m;
  LowLink graph(n, m);
  auto [a, b] = graph.low_link();
  sort(all(b));
  for (auto [s, t] : b) {
    cout << s << ' ' << t << '\n';
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
