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
  vector<vector<pair<int, int>>> tree(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v; cin >> u >> v;
    --u, --v;
    tree[u].emplace_back(v, i);
    tree[v].emplace_back(u, i);
  }

  const int M = 22;
  vector<vector<int>> p(n, vector<int>(M + 1));
  vector<int> dep(n);
  function<void(int, int)> dfs = [&](int u, int fa) {
    p[u][0] = fa, dep[u] = dep[fa] + 1;
    for (int i = 1; i <= M; i++) {
      p[u][i] = p[p[u][i - 1]][i - 1];
    }
    for (const auto &[v, id] : tree[u]) {
      if (v != fa) dfs(v, u);
    }
  };
  dfs(0, 0);

  function<int(int x, int y)> lca = [&](int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    for (int i = M; i >= 0; i--) {
      if (dep[p[v][i]] >= dep[u]) v = p[v][i];
    }
    if (u == v) return u;
    for (int i = M; i >= 0; i--) {
      if (p[u][i] != p[v][i]) {
        u = p[u][i], v = p[v][i];
      }
    }
    return p[u][0];
  };

  vector<int> cnt(n, 0);
  int q; cin >> q;
  for (int x, y; q--; ) {
    cin >> x >> y;
    --x, --y;
    int an = lca(x, y);
    cnt[x] += 1, cnt[y] += 1, cnt[an] -= 2;
  }

  vector<int> ans(n - 1, 0);
  function<void(int, int)> sol = [&](int u, int fa) {
    for (const auto &[v, id] : tree[u]) {
      if (v == fa) continue;
      sol(v, u);
      ans[id] = cnt[v];

      cnt[u] += cnt[v];
    }
  };
  sol(0, 0);

  for (int i = 0; i < n - 1; i++) {
    cout << ans[i] << " \n"[i + 1 == n - 1];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
