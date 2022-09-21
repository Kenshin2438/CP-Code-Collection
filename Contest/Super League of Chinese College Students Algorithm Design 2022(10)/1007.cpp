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

  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v; --u, --v;
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
  }

  vector<int> siz(n);
  int ans = 0;
  const function<void(int, int)> dfs = [&](int u, int fa) {
    siz[u] = 1;
    for (const int &v : tree[u]) {
      if (v == fa) continue;
      dfs(v, u);
      siz[u] += siz[v];
      ans += (siz[v] % 2 == 0);
    }
  };
  dfs(0, 0);

  const int mod = 998244353;
  ll res = 1;
  while (ans--) res = res * 2LL % mod;
  cout << (res - 1 + mod) % mod << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
