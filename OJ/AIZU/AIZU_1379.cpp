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
  for (auto &[x, y] : p) cin >> x >> y;
  vec<int> dp(1 << n);
  for (int mask = 0; mask < (1 << n); mask++) {
    if (__builtin_parity(mask)) continue;
    map<PII, int> line;
    for (int i = 0; i < n; i++) if (mask >> i & 1) {
      for (int j = 0; j < i; j++) if (mask >> j & 1) {
        int dx = p[i].fi - p[j].fi;
        int dy = p[i].se - p[j].se;
        int g = __gcd(dx, dy);
        dx /= g, dy /= g;
        if (dx < 0) dx *= -1, dy *= -1;
        line[PII{dx, dy}] ++;
      }
    }
    for (auto [_, num] : line) {
      dp[mask] = max(dp[mask], (num - 1) * num / 2);
    }
    for (int s = mask; s > 0; s = (s - 1) & mask) {
      if (__builtin_parity(s) == 0) {
        dp[mask] = max(dp[mask], dp[s] + dp[mask ^ s]);
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
