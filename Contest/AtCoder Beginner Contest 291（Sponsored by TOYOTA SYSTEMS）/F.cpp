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

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<pair<int, int>>> G(n), rG(n);
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    for (int j = 0; j < sz(s); j++) {
      if (s[j] == '1') {
        G[i].emplace_back(i + j + 1, 1);
        rG[i + j + 1].emplace_back(i, 1);
      }
    }
  }
  debug(G);

  static constexpr int inf = 0x3f3f3f3f;
  auto Dijkstra = [](const auto &G, int s) -> vector<int> {
    vector<int> dis(sz(G), inf);
    priority_queue<pair<int, int>> pq;
    pq.emplace(0, s), dis[s] = 0;
    while (!pq.empty()) {
      auto [du, u] = pq.top();
      pq.pop(), du = -du;
      if (dis[u] < du) continue;
      for (const auto &[v, d] : G[u]) {
        if (dis[v] > d + du) {
          dis[v] = d + du;
          pq.emplace(-dis[v], v);
        }
      }
    }
    return dis;
  };

  auto d = Dijkstra(G, 0);
  auto rd = Dijkstra(rG, n - 1);

  debug(d);
  debug(rd);

  for (int i = 1; i < n - 1; i++) {
    int ans = inf;
    for (int l = max(0, i - m); l < i; l++) {
      for (const auto &[v, _] : G[l]) {
        if (v > i) ans = min(ans, d[l] + 1 + rd[v]);
      }
    }
    cout << (ans >= inf ? -1 : ans) << " \n"[i + 1 == n - 1];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}