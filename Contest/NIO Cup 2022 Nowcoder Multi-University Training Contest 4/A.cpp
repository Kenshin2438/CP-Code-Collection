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
  int n, m; cin >> n >> m;
  vector<pair<ll, ll>> p(n);
  for (auto &&[w, q] : p) cin >> w;
  for (auto &&[w, q] : p) cin >> q;
  sort(all(p), [&](auto A, auto B) {
    return (A.second - 10000) * B.first >= (B.second - 10000) * A.first;
  });
  vector<double> dp(m + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    for (int j = m; j > 0; j--) {
      dp[j] = max(dp[j], dp[j - 1] * p[i].second / 10000.0 + p[i].first);
    }
  }
  cout << dp[m] << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
