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

const ll inf = 1e18;
struct edge {
  int to; ll weight;
  edge(int to, ll _ = inf) : to(to), weight(_) {}
};
int n, m, k;
vector<vector<edge>> G;
vector<ll> dis;

void Dijkstra() {
  priority_queue<pair<ll, int>> pq;
  for (int s = 1; s <= n; s++) pq.emplace(-dis[s], s);
  while (!pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop(), du = -du;
    if (dis[u] < du) continue;
    for (auto [v, d] : G[u]) {
      if (dis[v] > d + du) {
        dis[v] = d + du;
        pq.emplace(-dis[v], v);
      }
    }
  }
}

void solve() {
  cin >> n >> m >> k;

  G.resize(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v; ll w;
    cin >> u >> v >> w;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }

  dis.assign(n + 1, inf), dis[1] = 0;``
  Dijkstra();
  for (int _ = 0; _ < k; _++) {
    auto ndis = dis;
    for (int v = 1; v <= n; v++) {
      for (auto [u, w] : G[v]) {
        ndis[v] = min(ndis[v], dis[u] + w / 2);
      }
    }
    dis = move(ndis);
    Dijkstra();
  }
  cout << dis[n] << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
