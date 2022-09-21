#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int mod = 998244353;
ll inv[100], fac[100];

int n, k, t;
ll dp[100][100][10000];

void solve() {
  cin >> n >> k >> t;
  for (int i = 0; i <= n; i++) {
    dp[0][i][(i + 1) * i / 2] = inv[i];
  }
  for (int i = 1; i <= k - 1; i++) {
    for (int j = 0; j <= n; j++) {  // 选j个
      int pw = j * (j - 1) / 2;
      for (int jj = n; jj >= j; jj--) {
        for (int tt = t; tt >= pw; tt--) {
          dp[i][jj][tt] =
              (dp[i][jj][tt] + dp[i - 1][jj - j][tt - pw] * inv[j] % mod) % mod;
        }
      }
    }
  }
  cout << (fac[n] * dp[k - 1][n][t] % mod) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  fac[0] = fac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i < 100; i++) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = inv[mod % i] * (mod - mod / i) % mod;
  }
  for (int i = 2; i < 100; i++) {
    inv[i] = inv[i - 1] * inv[i] % mod;
  }

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
