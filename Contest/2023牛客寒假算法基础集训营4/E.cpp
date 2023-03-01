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
  int n, t, a; cin >> n >> t >> a;
  ll ans = 0;
  bool ok = true;
  for (int i = 0; i < n; i++) {
    ll h, v; cin >> h >> v;
    if (h <= a) ans += 1;
    else {
      ll d = a - t * v;
      if (d <= 0) {
        ok = false; 
        continue;
      }
      ans += (h - a + d - 1) / d + 1;
    }
  }
  if (ok == false) 
    cout << -1 << '\n';
  else 
    cout << (ans - 1) * t + 1 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}