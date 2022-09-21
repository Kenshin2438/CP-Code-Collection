#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) static_cast<int>(size(x))

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n; cin >> n;

  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];

  const int inf = 1e9;

  vector<int> dp(n + 1, inf); dp[0] = 0;
  for (int k = 1; k <= n; k++) {
    vector<int> ndp(n + 1, inf);

    // { max(a[i]), min(dp[i]), min(dp[i] + a[i]) }
    vector<array<int, 3>> s;
    s.push_back({ inf, inf, inf });
    for (int i = 1; i <= n; i++) {
      int cur = dp[i - 1];
      while (!s.empty() && s.back()[0] <= a[i]) {
        cur = min(cur, s.back()[1]); s.pop_back();
      }
      s.push_back({ a[i], cur, min(cur + a[i], s.back()[2]) });
      ndp[i] = s.back()[2];
    }

    dp = move(ndp);
    cout << dp[n] << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
