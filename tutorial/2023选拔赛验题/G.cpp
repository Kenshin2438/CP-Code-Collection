#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

pair<int, vector<int>> kosaraju(const vector<vector<int>> &G) {
  const int n = sz(G);

  vector<vector<int>> rG(n);
  for (int u = 0; u < n; u++) {
    for (const int &v : G[u]) {
      rG[v].emplace_back(u);
    }
  }

  vector<int> seq;
  vector<bool> vis(n, false);

  function<void(int)> dfs = [&](int u) {
    vis[u] = true;
    for (const int &v : G[u]) {
      if (vis[v] == false) dfs(v);
    }
    seq.emplace_back(u);
  };
  for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);

  int scc_num = 0;
  vector<int> scc(n);

  vis.assign(n, false);
  function<void(int)> rdfs = [&](int u) {
    vis[u] = 1, scc[u] = scc_num;
    for (int v : rG[u]) {
      if (vis[v] == false) rdfs(v);
    }
  };
  for (int i = n - 1; i >= 0; i--) {
    if (!vis[seq[i]]) rdfs(seq[i]), ++scc_num;
  }
  return {scc_num, scc};
}

ll Sn, Sm;

void solve() {
  int n, m; cin >> n >> m;
  assert(2 <= n && n <= (int) 5e5);
  Sn += n;
  assert(1 <= m && m <= (int) 5e5);
  Sm += m;

  vector<ll> p(n);
  for (auto &&x : p) {
    cin >> x;
    assert(1 <= x && x <= (int) 1e9);
  }

  vector<vector<int>> G(n);
  vector<bool> need(n, false);
  for (int _ = 0; _ < m; _++) {
    int u, v; cin >> u >> v;
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    assert(u != v);
    --u, --v;
    need[v] = true;
    G[v].emplace_back(u);
  }

  const auto &[scc_num, scc] = kosaraju(G);
  debug(scc);
  vector<int> d(scc_num);
  for (int u = 0; u < n; u++) {
    for (const int &v : G[u]) {
      if (scc[u] != scc[v]) {
        d[scc[v]] += 1;
      }
    }
  }

  vector<vector<ll>> scc_p(scc_num);
  for (int i = 0; i < n; i++) {
    if (need[i]) scc_p[scc[i]].emplace_back(p[i]);
  }

  ll ans = 0;
  for (int i = 0; i < scc_num; i++) {
    if (d[i] == 0 && !scc_p[i].empty()) {
      ans += *min_element(all(scc_p[i]));
    }
  }

  cout << ans << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  assert(1 <= T && T <= 10000);
  while (T--) solve();
  assert(1 <= Sn && Sn <= (int) 5e5);
  assert(1 <= Sm && Sm <= (int) 5e5);
  
  return 0;
}