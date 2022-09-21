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
  int n, D; cin >> n >> D;
  vector<ll> a(n);
  for (ll &x : a) cin >> x;

  sort(all(a));
  int l = 0, r = sz(a) - 1, ans = 0;
  while (l <= r) {
    if (a[r] > D) {
      ans += 1, r -= 1;
    } else {
      if ((r - l + 1) * a[r] <= D) break;
      ll cur = a[r];
      while (cur <= D && l < r) l++, cur += a[r];
      ans += 1, r -= 1;
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
