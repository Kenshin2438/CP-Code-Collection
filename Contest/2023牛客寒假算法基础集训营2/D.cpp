#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  int n; cin >> n;
  vector<vector<int>> tree(n);
  for (int i = 1; i < n; i++) {
    int f; cin >> f;
    tree[f - 1].emplace_back(i);
  }
  vector<ll> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  sort(all(v));

  vector<int> dep(n);
  const function<void(int, int)> dfs = [&](int u, int fa) {
    dep[u] = dep[fa] + 1;
    for (const int &v : tree[u]) {
      if (v != fa) dfs(v, u);
    }
  };
  dfs(0, 0);
  sort(all(dep));

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans += dep[i] * v[i];
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}