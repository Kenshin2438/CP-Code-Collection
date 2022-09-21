#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) static_cast<int>(size(x))

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n; cin >> n;
  const int mod = 998244353;

  ll ans = 1;
  for (int i = 0; i < n; i++) {
    ll x; cin >> x;
    ans = ans * (x + 1) % mod;
  }
  cout << (ans - 1 + mod) % mod << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
