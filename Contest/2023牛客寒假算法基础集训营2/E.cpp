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
  ll n, l, r; cin >> n >> l >> r;
  auto f = [n](ll x) { return n / x + x; };
  ll x = sqrtl(n);
  if (l > x) {
    cout << l << '\n';
  } else {
    if (f(x) >= f(x + 1)) x += 1;
    r = min(x, r);
    ll fans = f(r), ans;
    while (l <= r) {
      ll mid = (l + r) >> 1;
      if (f(mid) == fans) {
        ans = mid, r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    cout << ans << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}