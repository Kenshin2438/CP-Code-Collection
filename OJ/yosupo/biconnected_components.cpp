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
  int V, E;
  vector<vector<pair<int, int>>> to;
  vector<pair<int, int>> edges;

  vector<bool> is_bridge;
  vector<bool> is_articulation;

  vector<int> dfn, low, ids;

  int ecc_num;
  vector<int> ecc;

  int vcc_num;
  vector<int> vcc;

  LowLink(int _V, int _E) : V(_V), E(_E), to(V), edges(E) {
    for (int i = 0; i < E; i++) {
      int u, v; cin >> u >> v;
      to[u].emplace_back(v, i);
      to[v].emplace_back(u, i);
      edges[i].first  = u;
      edges[i].second = v;
    }
    is_bridge.assign(E, false);
    is_articulation.assign(V, false);
    dfn.assign(V, -1);
    low.assign(V, -1);
    ecc_num = vcc_num = 0;
    ecc.assign()
  }

  vector<int> stk;
  void tarjan(int u, int fa) {
    static int k = 0;

    dfn[u] = low[u] = k++;

  }

  void build() {
    for (int i = 0; i < V; i++) {
      if (dfn[i] == -1) tarjan(i, -1);
    }
    for (int i = 0; i < E; i++) {
      auto [u, v] = edges[i];
      if (dfn[u] > dfn[v]) swap(u, v);
      is_bridge[i] = dfn[u] < low[v];
    }
  }
};

void solve() {

}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
