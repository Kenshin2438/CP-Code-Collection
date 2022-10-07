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
  int n; cin >> n;
  vector<vector<int>> tree(n);

  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v;
    --u, --v;
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
  }

  int rt = 0;

  vector<int> ans(n, 0);
  const function<void(int, int)> dfs = [&](int u, int fa) {
    for (const int &v : tree[u]) {
      if (v == fa) continue;
      ans[rt] += v < u;
      dfs(v, u);
    }
  };
  dfs(rt, -1);

  const function<void(int, int)> sol = [&](int u, int fa) {
    for (const int &v : tree[u]) {
      if (v == fa) continue;
      ans[v] = ans[u] + (v < u ? -1 : 1);
      sol(v, u);
    }
  };
  sol(rt, -1);

  for (const int &x : ans) cout << x << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
