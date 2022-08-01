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
  int n; cin >> n;
  ll x; cin >> x;
  vector<ll> a(n);
  for (auto && ax : a) cin >> ax;

  // [ai - x, ai + x]
  const ll inf = 1e10;
  ll L = -inf, R = inf, ans = 0;
  for (const auto &ai : a) {
    L = max(L, ai - x);
    R = min(R, ai + x);

    if (L > R) ans += 1, L = ai - x, R = ai + x;
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
