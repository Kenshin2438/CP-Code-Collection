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
  int n, X; cin >> n >> X;
  vector<ll> a(n);
  for (auto &x : a) cin >> x;

  const auto lcm = [](ll a, ll b) -> ll {
    return a / gcd(a, b) * b;
  };

  ll ans = 0;
  for (int s = 1; s < (1 << n); s++) {
    ll f = 1;
    for (int i = 0; i < n; i++) {
      if (s >> i & 1) f = lcm(f, a[i]);
      if (f > X) { f = X + 1; break; } 
    }
    if (__builtin_parity(s)) {
      ans += X / f;
    } else {
      ans -= X / f;
    }
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