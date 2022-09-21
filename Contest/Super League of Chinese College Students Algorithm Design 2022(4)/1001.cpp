#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

const int mod = 1e9 + 7, N = 555;

int n, m, a[N];
ll f[N][N], g[N][N];

void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    for (int j = 1; j <= n; j++) {
      f[i][j] = g[i][j] = 0;
    }
    g[i][i - 1] = 1;
  }
  for (int len = 2; len <= n; len++) {
    for (int i = 1, j = len; j <= n; i++, j++) {
      if (a[i] == 0 && a[j] == 0) {
        f[i][j] = g[i + 1][j - 1] * m % mod;
      } else if (a[i] == 0 && a[j] != 0) {
        f[i][j] = g[i + 1][j - 1] * int(a[j] < 0) % mod;
      } else if (a[i] != 0 && a[j] == 0) {
        f[i][j] = g[i + 1][j - 1] * int(a[i] > 0) % mod;
      } else {
        f[i][j] = g[i + 1][j - 1] * int(a[i] > 0 && a[j] + a[i] == 0) % mod;
      }
      g[i][j] = f[i][j];
      for (int k = i; k < j; k++) {
        g[i][j] = (g[i][j] + g[i][k] * f[k + 1][j] % mod) % mod;
      }
    }
  }
  cout << g[1][n] << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) solve();
  return 0;
}
