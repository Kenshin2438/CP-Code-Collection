#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

struct DSU {
  vector<int> fa, sz;
  vector<pair<int&, int>> his_fa, his_sz;
  DSU(int n) : fa(n), sz(n) { init(); }
  void init() {
    fill(all(sz), 1), iota(all(fa), 0);
    his_sz.clear(), his_fa.clear();
  }
  int find(int x) {
    while (x != fa[x]) x = fa[x];
    return x;
  }
  bool same(int u, int v) {
    return find(u) == find(v);
  }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (sz[u] < sz[v]) swap(u, v);
    his_sz.emplace_back(sz[u], sz[u]);
    his_fa.emplace_back(fa[v], fa[v]);
    sz[u] += sz[v], fa[v] = u;
    return true;
  }
  int history() { return his_fa.size(); }
  void rollback(int h) {
    while ((int) his_fa.size() > h) {
      his_sz.back().first = his_sz.back().second;
      his_fa.back().first = his_fa.back().second;
      his_fa.pop_back(), his_sz.pop_back();
    }
  }
};

void solve() {
  const int N = 5e5 + 10;

  int n, m; cin >> n >> m;
  vector<array<int, 3>> E(m);
  vector<vector<int>> mapE(N);
  for (int i = 0; i < m; i++) {
    for (auto &x : E[i]) cin >> x;
    mapE[ E[i][2] ].push_back(i);
  }
  // assert(false);
  int q; cin >> q;
  vector<map<int, vector<int>>> mapQ(N);
  for (int i = 0; i < q; i++) {
    int k; cin >> k;
    while (k--) {
      int id; cin >> id; --id;
      mapQ[ E[id][2] ][i].push_back(id);
    }
  }
  DSU dsu(n + 1);
  vector<bool> ans(q, true);
  for (int w = 1; w <= 5e5; w++) {
    for (const auto &mp : mapQ[w]) {
      int now = dsu.history();
      for (const int id : mp.second) {
        if (dsu.merge(E[id][0], E[id][1]) == false) {
          ans[mp.first] = false; break;
        }
      }
      dsu.rollback(now);
    }
    for (const int &id : mapE[w]) {
      dsu.merge(E[id][0], E[id][1]);
    }
  }
  for (bool x : ans) cout << (x ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  // cin >> T;
  while (T--) solve();
  return 0;
}
