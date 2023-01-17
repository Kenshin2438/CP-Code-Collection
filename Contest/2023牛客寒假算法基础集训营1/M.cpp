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

double dp[505][505];
double ans(int n, int m) {
  if (n == 0 || m == 0) return 0.0;
  if (dp[n][m] != 0) return dp[n][m]; 
  for (int y = 0; y <= m; y++) {
    dp[n][m] = max(dp[n][m], (double)y / m + ans(n - 1, m - y));
  }
  return dp[n][m];
}

void solve() {
  int n, m; cin >> n >> m;
  cout << ans(n, m) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}