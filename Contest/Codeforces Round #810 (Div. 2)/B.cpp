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
  int n, m; cin >> n >> m;
  vector<ll> a(n);
  for (ll &x : a) cin >> x;

  vector<pair<int, int>> E(m);
  vector<int> d(n, 0);
  for (auto &&[u, v] : E) {
    cin >> u >> v, --u, --v;
    d[u] += 1, d[v] += 1;
  }

  vector<int> p;
  for (int i = 0; i < n; i++) {
    if (d[i] == 0) p.push_back(i);
  }
  if (m % 2 == 0) return cout << "0\n", void();

  ll ans = 1e18;
  for (const auto &[u, v] : E) {
    if ((d[u] + d[v] - 1) % 2 == 1) ans = min(ans, a[u] + a[v]);
  }
  for (int i = 0; i < n; i++) {
    if (d[i] & 1) ans = min(ans, a[i]);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
