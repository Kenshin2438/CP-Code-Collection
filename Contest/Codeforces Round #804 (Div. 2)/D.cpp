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
  vector<int> a(n);
  for (int &x : a) cin >> x;

  vector<vector<bool>> del(n, vector<bool>(n, false));
  for (int i = 0; i < n; i++) {
    int mx = 0;
    vector<int> cnt(n + 1, 0);
    for (int j = i; j < n; j++) {
      mx = max(mx, ++ cnt[ a[j] ]);
      if ((j - i + 1) % 2 == 0 && 2 * mx <= (j - i + 1)) {
        del[i][j] = true;
      }
    }
    if  (i + 1 < n) del[i + 1][i] = true;
  }
  vector<int> last(n + 1, -1), p(n);
  for (int i = 0; i < n; i++) {
    if (last[ a[i] ] == -1) {
      p[i] = i;
    } else {
      p[i] = last[ a[i] ];
    }
    last[ a[i] ] = i;
  }
  vector<int> dp(n, - 0x3f3f3f3f);
  for (int i = 0; i < n; i++) {
    if (i == 0 || del[0][i - 1]) dp[i] = 1;
  }
  // debug(p);
  // for (auto v : del) debug(v); 
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int j = i;
    while (j != p[j]) {
      j = p[j];
      if (del[j + 1][i - 1]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
    if (i == n - 1 || del[i + 1][n - 1]) ans = max(ans, dp[i]);
  }
  // debug(dp);
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) solve();
  return 0;
}