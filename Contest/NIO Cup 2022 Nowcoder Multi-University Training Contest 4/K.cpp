#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int N = 1e7 + 10;

void solve() {
  int n; cin >> n;

  if (n == 1) return cout << 0 << '\n', void();

  vector<ll> pw(N);
  for (int i = pw[0] = 1; i < N; i++) {
    pw[i] = pw[i - 1] * 10LL % n;
  }

  ll ans = 0LL;
  for (int i = 1; i <= n; i++) {
    for (int k = 1; k < N; k++) {
      int x = (i + n - (i - 1) * 1LL * pw[k] % n) % n;
      int len = to_string(x).length();
      if (len <= k) {
        ans += k;
        break;
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
