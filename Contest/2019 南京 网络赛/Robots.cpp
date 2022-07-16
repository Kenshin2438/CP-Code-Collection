#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> G(n);
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    --u, --v;
    G[u].emplace_back(v);
  }
  // start at 0, arrive at (n - 1)
  vector<double> f(n), g(n);
  function<void(int)> dfs = [&](int u) {
    if (u == n - 1) return;
    if (f[u] != 0 || g[u] != 0) return;
    double F = 1.0, S = 0.0;
    for (int v : G[u]) {
      dfs(v);
      F += f[v] + 1.0;
      S += g[v];
    }
    f[u] = F / G[u].size();
    g[u] = (S + f[u] * (G[u].size() + 1)) / G[u].size();
  };
  dfs(0);
  cout << g[0] << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(2);

  int T; cin >> T;
  while (T--) solve();
  
  return 0;
}