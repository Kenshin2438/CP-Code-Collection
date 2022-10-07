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
  ll n; cin >> n;
  ll ans = 1;
  for (ll x = 2; x * x <= n; x++) if (n % x == 0) {
    int e = 0;
    while (n % x == 0) n /= x, e += 1;
    if (e & 1) ans *= x;
  }
  if (n != 1LL) ans *= n;

  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
