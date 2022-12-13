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

struct SCC {
  vector<int> scc;
  vector<vector<int>> G, rG;
  int n;

  SCC(const vector<vector<int>> &_G) : G(_G) {
    this->n = sz(G);
    scc.resize(n), rG.resize(n);
    for (int u = 0; u < n; u++) {
      for (const int &v : G[u]) {
        rG[v].emplace_back(u);
      }
    }
  }
  pair<int, vector<int>> kosaraju() {
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

    vis.assign(n, false);
    int scc_num = 0;
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
};

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> G(n);
  for (int _ = m; _--;) {
    for (int pre = -1, i = 0; i < n; i++) {
      int x; cin >> x; x -= 1;
      if (~pre) G[x].emplace_back(pre);
      pre = x;
    }
  }
  for (int i = 0; i < n; i++) {
    sort(all(G[i]));
    G[i].erase(unique(all(G[i])), end(G[i]));
  }

  const auto &[scc_num, scc] = SCC(G).kosaraju();
  vector<int> comp_size(scc_num, 0);
  for (int i = 0; i < n; i++) comp_size[scc[i]]++;

  vector<vector<int>> scc_graph(scc_num);
  for (int i = 0; i < n; i++) {
    for (const int &j : G[i]) {
      if (scc[i] == scc[j]) continue;
      scc_graph[scc[i]].emplace_back(scc[j]);
    }
  }
  for (int i = 0; i < scc_num; i++) {
    sort(all(scc_graph[i]));
    scc_graph[i].erase(unique(all(scc_graph[i])), end(scc_graph[i]));
  }
  vector<int> d(scc_num);
  for (int i = 0; i < scc_num; i++) {
    for (const int &j : scc_graph[i]) {
      d[j]++;
    }
  }

  {
    // 0-indexed
    // `G` denotes the Graph
    // `d` denotes the in-degree
    queue<int> Q;
    for (int i = 0; i < sz(d); i++) {
      if (d[i] == 0) Q.push(i);
    }
    vector<int> topo;
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      topo.emplace_back(u);
      for (const int &v : scc_graph[u]) {
        comp_size[v] += comp_size[u];
        if (--d[v] == 0) Q.push(v);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << comp_size[scc[i]] - 1 << " \n"[i + 1 == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
