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
  int n, x, y; cin >> n >> x >> y;
  x = min(x, 2 * y);

  string a, b; cin >> a >> b;
  vector<int> p;
  for (int i = 0; i < n; i++) {
    if (a[i] != b[i]) p.push_back(i);
  }

  if (p.empty()) return cout <<  "0\n", void();
  if (sz(p) & 1) return cout << "-1\n", void();

  ll ans = 0;
  if (y <= x) {
    if (sz(p) == 2 && p[0] + 1 == p[1]) {
      ans = x;
    } else {
      ans = sz(p) / 2 * 1LL * y;
    }
  } else {
    vector<ll> dp(sz(p) + 1);
    for (int i = 2; i <= sz(p); i++) {
      dp[i] = max(dp[i - 1], dp[i - 2] + y - x * 1LL * (p[i - 1] - p[i - 2]));
    }
    ans = sz(p) / 2 * 1LL * y - dp.back();
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
