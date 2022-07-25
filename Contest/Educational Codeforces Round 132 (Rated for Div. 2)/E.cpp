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
  vector<vector<int>> tree(n);
  vector<int> val(n);
  for (int &x : val) cin >> x;
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    --u, --v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  int ans = 0;
  vector<set<int>> S(n);
  vector<int> X(n);
  function<void(int, int)> dfs = [&](int u, int fa) {
    S[u].insert(X[u] = val[u] ^ X[fa]);
    bool tg = false;
    for (const int &v : tree[u]) {
      if (v == fa) continue;
      dfs(v, u);
      if (S[u].size() < S[v].size()) swap(S[u], S[v]);
      for (const int &x : S[v]) {
        if (S[u].count(x ^ val[u])) tg = true;
      }
      S[u].merge(S[v]), S[v].clear();
    }
    if (tg) ans += 1, S[u].clear();
  };
  dfs(0, 0);
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
