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
  int n, k; cin >> n >> k;
  vector<vector<int>> G(n + 1);
  for (int i = 1; i <= n - 1; i++) {
    int u, v; cin >> u >> v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  vector<int> ans;
  priority_queue<int, vector<int>, greater<int>> pq;
  vector<int> dep(n + 1, -1);
  const function<void(int, int, int)> dfs = [&](int u, int fa, int d) {
    if (dep[u] >= d) return;
    if (dep[u] == -1) pq.push(u);
    dep[u] = d;
    if (d == 0) return;
    for (const int &v : G[u]) {
      if (v == fa) continue;
      dfs(v, u, d - 1);
    }
  };
  ans.emplace_back(1), dfs(1, 0, k);
  while (!pq.empty()) {
    int u = pq.top(); pq.pop();
    if (u == 1) continue;
    ans.emplace_back(u);
    dfs(u, 0, k);
  }
  for (int i = 0; i < n; i++) {
    cout << ans[i] << " \n"[i + 1 == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
