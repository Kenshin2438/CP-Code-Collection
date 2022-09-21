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

void solve() {
  int n, m; cin >> n >> m;
  const ll inf = 1e18;
  vector<vector<pair<int, ll>>> G(n), rG(n);
  for (int i = 0; i < m; i++) {
    int u, v; ll w;
    cin >> u >> v >> w;
    --u, --v;
    G[u].emplace_back(v, w);
    rG[v].emplace_back(u, w);
  }

  vector<ll> dis(n, inf);
  priority_queue<pair<ll, int>> pq;
  pq.emplace(dis[0] = 0, 0);
  while (!pq.empty()) {
    auto [D, u] = pq.top(); pq.pop();
    D = -D;
    if (D > dis[u]) continue;
    for (const auto &[v, d] : G[u]) {
      if (dis[v] > D + d) {
        dis[v] = D + d, pq.emplace(-dis[v], v);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    pq.emplace(-dis[i], i);
  }
  while (!pq.empty()) {
    auto [D, u] = pq.top(); pq.pop();
    D = -D;
    if (-D > dis[u]) continue;
    for (const auto &[v, d] : rG[u]) {
      if (dis[v] > D + d) {
        dis[v] = D + d, pq.emplace(-dis[v], v);
      }
    }
  }
  for (int i = 1; i < n; i++) {
    cout << (dis[i] == inf ? -1 : dis[i]) << " \n"[i + 1 == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
