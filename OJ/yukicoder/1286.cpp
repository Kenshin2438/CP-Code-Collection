#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  ll D; cin >> D;
  const auto f = [](int t, ll x) -> ll {
    ll res = 0;
    while (t-- && x) res += x, x >>= 1;
    return res;
  };
  ll ans = D;
  for (int t = 1; t < 65; t++) {
    ll l = 1, r = D, tmp = D;
    while (l <= r) {
      ll m = (l + r) >> 1;
      ll fm = f(t, m);
      if (fm >= D) {
        tmp = m;
        r = m - 1;
      } else {
        l = m + 1;
      }
    }
    if (f(t, tmp) == D) ans = min(ans, tmp);
  }
  cout << ans << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}