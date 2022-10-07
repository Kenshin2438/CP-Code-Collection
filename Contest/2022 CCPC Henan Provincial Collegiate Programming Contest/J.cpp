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
  vector<int> val(n), node(n);
  for (int i = 0; i < n; i++) {
    cin >> val[i], node[val[i]] = i;
  }

  vector<vector<int>> tree(n);
  for (int i = 1; i < n; i++) {
    int x; cin >> x; --x;
    tree[x].emplace_back(i);
    tree[i].emplace_back(x);
  }

  vector<int> siz(n, 1), Min(n);
  const function<void(int, int)> dfs = [&](int u, int fa) {
    siz[u] = 1, Min[u] = val[u];
    for (const int &v : tree[u]) {
      if (v == fa) continue;
      dfs(v, u);
      siz[u] += siz[v];
      Min[u] = min(Min[u], Min[v]);
    }
  };
  dfs(node[0], -1);

  vector<int> ans(n + 1);
  ans[n] = n;
  ans[0] = [&]() -> int {
    int res = 0;
    for (const int &v : tree[node[0]]) res = max(res, siz[v]);
    return res;
  }();

  for (int i = 1; i < n; i++) {
    if (Min[node[i]] >= i) ans[i] = n - siz[node[i]];
    else ans[i] = 0;
  }

  for (int i = 0; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
