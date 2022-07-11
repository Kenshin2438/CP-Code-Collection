#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n; cin >> n;
  vector<vector<int>> G(n);
  bool ans = true;
  for (int i = 1; i <= n; i++) {
    int u, v; cin >> u >> v;
    --u, --v;
    G[u].push_back(v);
    G[v].push_back(u);
    if (u == v) ans = false;
  }
  for (int i = 0; i < n; i++) {
    if (G[i].size() >= 3) ans = false;
  }
  if (ans == false) return cout << "NO\n", void();

  vector<bool> vis(n, false);
  for (int i = 0; i < n; i++) {
    if (vis[i]) continue;

    int cnt = 0;
    auto dfs = [&](auto &&self, int u, int fa) {
      if (vis[u]) return ;
      cnt ++, vis[u] = true;
      for (int v : G[u]) {
        if (v == fa) continue;
        self(self, v, u);
      }
    };
    dfs(dfs, i, i);
    if (cnt & 1) ans = false;
  }
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T; cin >> T;
  while (T--) solve();
  return 0;
}