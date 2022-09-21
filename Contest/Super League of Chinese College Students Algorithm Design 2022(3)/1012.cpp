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
const int N = 3e5 + 50;

int n, a[N], b[N], s[N * 2], pa[N], pb[N];
ll dp[N * 2][2];

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    pa[ a[i] ] = i;
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
    pb[ b[i] ] = i;
  }
  for (int i = 1; i <= n * 2; i++) {
    cin >> s[i];
  }
  for (int i = 1; i <= n * 2; i++) {
    int x = s[i];
    if (i == 1) {
      if (pa[x] == 1) dp[i][0] = 1;
      if (pb[x] == 1) dp[i][1] = 1;
    } else {
      { // dp[i][0]
        if (pa[ s[i - 1] ] + 1 == pa[ s[i] ]) dp[i][0] += dp[i - 1][0];
        if (i - pb[ s[i - 1] ] == pa[ s[i] ]) dp[i][0] += dp[i - 1][1];
      }
      { // dp[i][1]
        if (pb[ s[i - 1] ] + 1 == pb[ s[i] ]) dp[i][1] += dp[i - 1][1];
        if (i - pa[ s[i - 1] ] == pb[ s[i] ]) dp[i][1] += dp[i - 1][0];
      }
      dp[i][0] %= mod, dp[i][1] %= mod;
    }
  }
  ll ans = (dp[n * 2][0] + dp[n * 2][1]) % mod;
  cout << ans << '\n';
  for (int i = 0; i <= n * 2; i++) {
    dp[i][0] = dp[i][1] = 0;
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
