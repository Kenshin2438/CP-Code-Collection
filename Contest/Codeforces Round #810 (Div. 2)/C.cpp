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
  ll n, m, k; cin >> n >> m >> k;
  vector<ll> a(k);
  for (ll &x : a) cin >> x;
  bool ans = false;
  {
    ll A = 0; bool B = false;
    for (ll x : a) {
      ll t = x / n;
      if (t <= 1) continue;
      A += t;
      if (t > 2) B = true;
    }
    if (m & 1) {
      if (B && A >= m) ans = true;
    } else {
      if (A >= m) ans = true;
    }
  }
  swap(n, m);
  {
    ll A = 0; bool B = false;
    for (ll x : a) {
      ll t = x / n;
      if (t <= 1) continue;
      A += t;
      if (t > 2) B = true;
    }
    if (m & 1) {
      if (B && A >= m) ans = true;
    } else {
      if (A >= m) ans = true;
    }
  }
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
