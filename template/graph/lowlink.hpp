#include "../main.hpp"

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
