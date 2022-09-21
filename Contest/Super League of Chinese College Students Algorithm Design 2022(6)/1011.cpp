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
  int n, k; cin >> n >> k;
  for (int i = 1; i <= n; i += 1) {
    ll ans = 0;
    for (int d = 1; d * d <= i; d += 1) {
      if (i % d == 0) {
        ans = (ans + phi[d] * pw[i / d]) % mod;
        if (d * d != n) {
          sum +=
        }
      }
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
