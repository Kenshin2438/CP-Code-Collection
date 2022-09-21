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
  int n, m, ans = 1e9; cin >> n >> m;
  vector<int> p(m, -1e9);
  p[0] = 0;

  for (int i = 1; i <= n; i++) {
    int sz; cin >> sz;
    auto np = p;
    while (sz--) {
      int u, v; cin >> u >> v;
      --u, --v;

      if (v == 0) continue;
      if (u == 0) np[v] = i;
      else np[v] = max(np[v], p[u]);

      if (v == m - 1 && p[u] != -1e9) {
        ans = min(ans, i - np[v] + 1);
      }
    }
    p = move(np);
  }

  cout << (ans == 1e9 ? -1 : ans) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
