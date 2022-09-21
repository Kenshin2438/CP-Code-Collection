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
  ll a, b, c, t;
  cin >> a >> b >> c >> t;
  if (c == t) return cout << "Yes\n", void();
  if (b == a - b) {
    if (c == t || b - c == t) cout << "Yes\n";
    else cout << "No\n";

    return;
  } else {
    ll x = b, y = a - b;
    if ((t - c) % (x - y) == 0 || (t - c) % (y - x) == 0) return cout << "Yes\n", void();
    if ((t + c - x) % (x - y) == 0 || (t + c - y) % (y - x) == 0) return cout << "Yes\n", void();
    return cout << "No\n", void();
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
