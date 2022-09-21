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
  int n, K; cin >> n >> K;
  vector<int> d(n);
  for (int &x : d) cin >> x;

  vector<vector<ll>> dp(1 << n, vector<ll>(K, -1));
  dp[0][0] = 0;
  for (int mask = 1; mask < (1 << n); mask++) {
    for (int i = 0; i < n; i++) if (mask >> i & 1) {
      int U = mask ^ (1 << i);
      for (int r = 0; r < K; r++) if (~dp[U][r]) {
        int t = (r * 10 + d[i]) % K;
        dp[mask][t] = max(dp[mask][t], dp[U][r] * 10LL + d[i]);
      }
    }
  }
  const auto &ans = dp.back();
  for (int i = K - 1; i >= 0; i--) {
    if (~ans[i]) return cout << ans[i] << '\n', void();
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
