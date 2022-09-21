#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

struct LowLink {
  vector<int> articulation_points;
  vector<pair<int, int>> bridges;

  int n, m, idx;
  vector<vector<int>> G;
  vector<int> dfn, low;

  LowLink(int _n, int _m) : n(_n), m(_m), G(n) {
    for (int u, v, _ = 0; _ < m; _++) {
      cin >> u >> v;
      // --u, --v
      G[u].emplace_back(v);
      G[v].emplace_back(u);
    }
  }

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

  pair<vector<int>, vector<pair<int, int>>> low_link() {
    dfn.assign(n, 0);
    low.assign(n, 0);
    articulation_points.clear();
    bridges.clear();
    idx = 0;  // init
    for (int i = 0; i < n; i++) {
      if (dfn[i] == 0) tarjan(i, -1);
    }
    return {articulation_points, bridges};
  }
};

int treeDiameter(const vector<vector<int>> &tree) {
  vector<int> d1(sz(tree)), d2(sz(tree));
  int d = 0;
  function<void(int, int)> dfs = [&](int u, int fa) {
    d1[u] = d2[u] = 0;
    for (const int &v : tree[u]) {
      if (v == fa) continue;
      dfs(v, u);
      int t = d1[v] + 1;
      if (t > d1[u]) d2[u] = d1[u], d1[u] = t;
      else if (t > d2[u]) d2[u] = t;
    }
    d = max(d, d1[u] + d2[u]);
  };
  return dfs(0, 0), d;
}

void solve() {
  int n, m; cin >> n >> m;
  LowLink sol(n, m);

  const auto &G = sol.G;
  const auto &bridges = sol.low_link().second;
  set<pair<int, int>> S(all(bridges));

  int edcc_num = 0;
  vector<int> edcc(n);
  vector<bool> vis(n, false);
  const function<void(int)> dfs = [&](int u) {
    vis[u] = true, edcc[u] = edcc_num;
    for (const int &v : G[u]) {
      if (vis[v] || S.count(minmax(v, u))) continue;
      dfs(v);
    }
  };
  for (int i = 0; i < n; i++) {
    if (vis[i] == false) dfs(i), ++edcc_num;
  }
  debug(edcc);

  vector<vector<int>> tree(edcc_num);
  for (const auto &[u, v] : bridges) {
    tree[edcc[u]].emplace_back(edcc[v]);
    tree[edcc[v]].emplace_back(edcc[u]);
  }

  cout << treeDiameter(tree) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
