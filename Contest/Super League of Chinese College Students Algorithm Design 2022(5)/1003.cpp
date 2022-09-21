#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n; cin >> n;
  vector<vector<array<int, 2>>> G(n);
  for (int i = 1; i < n; i++) {
    int u, v, w; cin >> u >> v >> w;
    --u, --v;
    G[u].push_back({v, w});
    G[v].push_back({u, w});
  }
  vector<int> dep(n);
  vector<vector<int>> S(n + 1);
  function<void(int, int)> dfs = [&](int u, int fa) {
    dep[u] = dep[fa] + 1;
    for (const auto &a : G[u]) {
      if (a[0] == fa) continue;
      dfs(a[0], u);
    }
    S[dep[u]].push_back(u);
  };
  dfs(0, 0);
  debug(S);
  int k, p; cin >> k >> p;
  int s, t; cin >> s >> t;
  --s, --t;
  vector<ll> dis(n, 1e18), DIS(n + 1, 1e18);
  priority_queue<tuple<ll, int, bool>> pq;
  pq.emplace(dis[s] = 0LL, s, false);
  while (!pq.empty()) {
    ll D; int u; bool tag;
    tie(D, u, tag) = pq.top();
    pq.pop();
    D = -D;
    if (tag) {
      if (D > DIS[u]) continue;
      for (const int &v : S[u]) {
        if (dis[v] > D + p) {
          dis[v] = D + p;
          pq.emplace(-dis[v], v, false);
        }
      }
    } else {
      if (D > dis[u]) continue;
      for (const auto &a : G[u]) {
        int v = a[0], w = a[1];
        if (dis[v] > D + w) {
          dis[v] = D + w;
          pq.emplace(-dis[v], v, false);
        }
      }
      int h = dep[u];
      if (h - k >= 1) {
        if (DIS[h - k] > dis[u]) {
          DIS[h - k] = dis[u];
          pq.emplace(-DIS[h - k], h - k, true);
        }
      }
      if (h + k <= n) {
        if (DIS[h + k] > dis[u]) {
          DIS[h + k] = dis[u];
          pq.emplace(-DIS[h + k], h + k, true);
        }
      }
    }
  }
  cout << dis[t] << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
