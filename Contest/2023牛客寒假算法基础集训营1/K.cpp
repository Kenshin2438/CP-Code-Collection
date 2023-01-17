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

const int N = 1000 + 10;
const long long inf = 1e18;
long long dp[N][N][4];

void init() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < 4; k++) {
        dp[i][j][k] = inf;
      }
    }
  }
  dp[2][0][0] = 0;
  dp[2][1][1] = dp[2][1][2] = 0;
  dp[2][2][3] = 0;
}

void solve() {
  int n, m; cin >> n >> m;
  if (n < 3 || m == 0 || n - m >= 2 * (m - 1))
    return cout << 0 << '\n', void();
  if (n == 3) {
    if (m == 1 || m == 0) return cout << 0 << '\n', void();
    else return cout << 1 << '\n', void();
  }
  init();
  for (int i = 3; i <= n; i++) {
    for (int j = 0; j <= min(m, i); j++) {
      { // 0
        dp[i][j][0] = min(dp[i-1][j][0], dp[i-1][j][1]);
        dp[i][j][1] = min(dp[i-1][j][2], dp[i-1][j][3] + 1);
      }
      if (j > 0) { // 1
        dp[i][j][2] = min(dp[i-1][j-1][0], dp[i-1][j-1][1] + 1);
        dp[i][j][3] = min(dp[i-1][j-1][2] + 1, dp[i-1][j-1][3] + 1);
      }
    }
  }
  cout << min({dp[n][m][0], dp[n][m][1], dp[n][m][2], dp[n][m][3]}) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}