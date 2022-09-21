struct SCC {
  vector<int> scc;
  int n, m;
  vector<vector<int>> G, rG;

  SCC(int _n, int _m) : n(_n), m(_m), G(n), rG(n) {
    for (int u, v, _ = 0; _ < m; _++) {
      cin >> u >> v; --u, --v;
      G[u].emplace_back(v);
      rG[v].emplace_back(u);
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
