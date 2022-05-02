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

class SCC {
private:
  int cnt;
  vec<int> scc;

  int n, m, idx;
  vec<vec<int>> G, rG;

public:
  SCC(int _n, int _m) : n(_n), m(_m), G(n), rG(n) {
    for (int u, v, _ = 0; _ < m; _++) {
      cin >> u >> v;
      G[u].emplace_back(v);
      rG[v].emplace_back(u);
    }
  }
  pair<int, vec<int>> kosaraju() {
    vec<int> seq, vis(n, 0);
    auto dfs = [&](auto && self, int u) -> void {
      vis[u] = 1;
      for (int v : G[u]) {
        if (vis[v] == 0) self(self, v);
      }
      seq.emplace_back(u);
    };
    for (int i = 0; i < n; i++) if (vis[i] == 0) dfs(dfs, i);
    vis.assign(n, 0);
    scc.assign(n, 0);
    cnt = 0;
    auto rdfs = [&](auto && self, int u) -> void {
      vis[u] = 1, scc[u] = cnt;
      for (int v : rG[u]) {
        if (vis[v] == 0) self(self, v);
      }
    };
    for (int i = n - 1; i >= 0; i--) {
      if (vis[seq[i]] == 0) ++cnt, rdfs(rdfs, seq[i]);
    }
    return {cnt, scc};
  }
};

void SingleTest(int TestCase) {
  int n, m; cin >> n >> m;
  SCC graph(n, m);
  auto [_, scc] = graph.kosaraju();
  int Q; cin >> Q;
  for (int u, v; Q--; ) {
    cin >> u >> v;
    cout << int(scc[u] == scc[v]) << '\n';
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
