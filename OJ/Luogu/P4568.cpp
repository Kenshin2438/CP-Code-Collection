#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int n, m, k; cin >> n >> m >> k;
  k = min(k, m);
  int s, t; cin >> s >> t;
  vector<vector<pair<int, int>>> G(n);
  for (int i = 0; i < m; i++) {
    int u, v, w; cin >> u >> v >> w;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  const int inf = 0x3f3f3f3f;
  vector<vector<int>> dis(k + 1, vector<int>(n, inf));
  priority_queue<array<int, 3>> pq; // dis, node, cur
  dis[0][s] = 0;
  pq.push({ -dis[0][s], s, 0 });
  while (!pq.empty()) {
    auto [d, u, o] = pq.top();
    pq.pop();
    if (dis[o][u] < -d) continue;
    for (const auto &[v, w] : G[u]) {
      if (o + 1 <= k && dis[o + 1][v] > dis[o][u]) {
        dis[o + 1][v] = dis[o][u];
        pq.push({ -dis[o + 1][v], v, o + 1 });
      }
      if (dis[o][v] > dis[o][u] + w) {
        dis[o][v] = dis[o][u] + w;
        pq.push({ -dis[o][v], v, o });
      }
    }
  }
  cout << dis[k][t] << '\n';
  return 0;
}