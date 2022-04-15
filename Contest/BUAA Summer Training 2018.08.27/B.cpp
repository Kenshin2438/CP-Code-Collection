#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) a.begin(), a.end()

using db = double;
using ll = long long;

void SingleTest(int TestCase) {
  int n; cin >> n;
  vec<PII> p(n);
  vec<int> dp(1 << n);
  for (int i = 0; i < n; i++) {
    cin >> p[i].fi >> p[i].se;
  }
  for (int s = 0, ss = 1 << n; s < ss; s++) {
    if (__builtin_parity(s)) continue;
    map<PII, int> ans;
    for (int i = 0; i < n; i++) {
      if (s >> i & 1) for (int j = 0; j < i; j++) {
        if (s >> j & 1) {
          int dx = p[i].fi - p[j].fi;
          int dy = p[i].se - p[j].se;
          int g = __gcd(dx, dy);
          dx /= g, dy /= g;
          if (dx < 0) dx *= -1, dy *= -1;
          ans[PII{dx, dy}] ++;
        }
      }
    }
    // debug(bitset<8>(s), ans);
    for (auto it = ans.begin(); it != ans.end(); it = next(it)) {
      dp[s] = max(dp[s], (it->se - 1) * (it->se) / 2);
    }
    // debug(bitset<8>(s), dp[s]);
    for (int s0 = (s - 1) & s; s0; s0 = (s0 - 1) & s) {
      if ((s0 & (s & -s)) && __builtin_parity(s0) == 0) {
        dp[s] = max(dp[s], dp[s0] + dp[s ^ s0]);
      }
    }
  }
  cout << dp[(1 << n) - 1] << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
