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
  int n, m, k; cin >> n >> m >> k;
  assert(1 <= n && n <= 3000);
  assert(1 <= m && m <= 3000);
  assert(1 <= k && k <= 3000);

  vector<array<ll, 3>> p(n);
  for (auto &&[x, _, __] : p) {
    cin >> x;
    assert(1 <= x && x <= 3000);
  }
  for (auto &&[_, x, __] : p) {
    cin >> x;
    assert(1 <= x && x <= 3000);
  }
  for (auto &&[_, __, x] : p) {
    cin >> x;
    assert(1 <= x && x <= (ll) 1e12);
  }
  sort(all(p));

  static constexpr ll inf = (ll) 1e18;
  vector<ll> dp(m + 3000, inf);
  dp[0] = 0;
  for (const auto &[d, f, t] : p) {
    vector<ll> ndp = dp;
    for (int v = max<int>(0, d - k); v + f < m + 3000; v++) {
      ndp[v + f] = min(ndp[v + f], dp[v] + t);
    }
    dp = move(ndp);
  }
  ll ans = *min_element(m + all(dp));
  cout << (ans >= inf ? -1 : ans) << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}