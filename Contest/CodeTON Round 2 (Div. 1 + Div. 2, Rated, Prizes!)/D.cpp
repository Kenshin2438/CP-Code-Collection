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
  vector g(n, vector<ll>(m));
  for (auto &&v : g) for (ll &x : v) cin >> x;

  vector<ll> cnt(n);
  for (int i = 0; i < n; i++) {
    for (int j = m - 1; j >= 1; j--) {
      if (g[i][j]) cnt[i] += g[i][j], g[i][j-1] += g[i][j];
    }
  }
  cout << int(max_element(all(cnt)) - begin(cnt) + 1) << ' ';
  cout << (*max_element(all(cnt)) - *min_element(all(cnt))) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
