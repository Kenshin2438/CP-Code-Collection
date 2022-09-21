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
  ll n; cin >> n;
  int ans = __builtin_popcountll(n);
  vector<ll> f = { 6 };
  for (int i = 4; f.back() * i <= n; i++) {
    f.push_back(f.back() * i);
  }
  int m = f.size();
  debug(m, f);
  for (int mask = 0; mask < (1 << m); mask++) {
    ll S = 0LL;
    for (int i = 0; i < m; i++) if (mask >> i & 1) {
      S += f[i];
    }
    if (n >= S)
      ans = min(ans, __builtin_popcountll(mask) + __builtin_popcountll(n - S));
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
