#include "../data_structure/sparse_table.hpp"
#include "../main.hpp"

struct Graph {
  vector<pair<int, int>> euler_tour;
  vector<int> dfn;
  ST<pair<int, int>, Min<pair<int, int>>> st;

  int n, rt;
  vector<vector<int>> G;

  Graph(int _, int _rt = 0) : n(_), rt(_rt), G(_) {
    for (int i = 0; i < n; i++) {
      int m, x;
      cin >> m;
      while (m--) {
        cin >> x;
        G[i].emplace_back(x);
      }
    }
    dfn.assign(n, 0);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
      dfn[u] = euler_tour.size();
      euler_tour.emplace_back(dfn[u], u);
      for (const int &v : G[u]) {
        if (v == fa) continue;
        self(self, v, u);
        euler_tour.emplace_back(dfn[u], u);
      }
    };
    dfs(dfs, rt, -1);
    st = ST<pair<int, int>, Min<pair<int, int>>>(euler_tour);
  }

  int lca(int u, int v) {
    int l = dfn[u], r = dfn[v];
    if (l > r) swap(l, r);
    return st.query(l, r + 1).second;
  }
};
