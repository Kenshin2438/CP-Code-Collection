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
  vector<vector<double>> p(n, vector<double>(n));
  for (auto &&v : p) for (auto &&x : v) cin >> x;

  vector<vector<double>> dp(n + 1, vector<double>(1 << n));
  dp[0].back() = 1;
  for (int i = 1; i <= n; i++) {
    for (int mask = 0; mask < (1 << n); mask++) {
      if (__builtin_popcount(mask) + i != n) continue;
      for (int j = 0; j < n; j++) if (!(mask >> j & 1)) {
        for (int k = 0; k < n; k++) if (mask >> k & 1) {
          dp[i][mask] += dp[i - 1][mask | (1 << j)] * p[k][j];
        }
      }
      dp[i][mask] /= (n - i + 1) * (n - i) / 2;
    }
  }
  for (int i = 0; i < n; i++) {
    cout << dp[n - 1][1 << i] << " \n"[i + 1 == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(6);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
