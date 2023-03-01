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
  int n, m; cin >> n >> m;
  vector<vector<int>> G(n);
  vector<int> d(n);
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    --u, --v;
    G[u].emplace_back(v);
    d[v] += 1;
  }

  vector<int> ans(n, 1);
  queue<int> Q;
  for (int i = 0; i < (int)d.size(); i++) {
    if (d[i] == 0) Q.push(i);
  }
  if (sz(Q) != 1) return cout << "No\n", void();
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    for (const int &v : G[u]) {
      ans[v] = max(ans[v], ans[u] + 1);
      if (--d[v] == 0) Q.push(v);
    }
  }
  if (sz(set(all(ans))) != n) return cout << "No\n", void();
  cout << "Yes\n";
  for (int i = 0; i < n; i++) {
    cout << ans[i] << " \n"[i + 1 == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}