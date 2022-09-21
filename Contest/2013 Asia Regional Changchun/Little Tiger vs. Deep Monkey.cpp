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
  int n; double p;
  cin >> n >> p;

  vector<int> s(n);
  for (int &x : s) cin >> x;

  const int N = 1000 * n + 10;
  vector<double> dp(N);
  dp[0] = 1;

  for (const int &x : s) {
    vector<double> ndp(N);
    for (int i = 0; i < N; i++) {
      ndp[i] = dp[i] / 2;
      if (i - x >= 0) ndp[i] += dp[i - x] / 2;
    }
    dp = move(ndp);
  }

  double P = 0;
  for (int i = 0; i < N; i++) {
    P += dp[i];
    if (P >= p) return cout << i << '\n', void();
  }

}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
