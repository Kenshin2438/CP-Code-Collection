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

const int mod = 998244353;
const int phi = mod - 1;

ll qpow(ll x, ll n, ll mod) {
  ll res = 1;
  for (; n; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return res;
}
const int inv3 = 332748118;

void solve() {
  string s; cin >> s;

  ll K = 0;
  for (const char &c : s) {
    K = (K * 10LL + (c & 15)) % phi;
  }

  bool odd = int(s.back() & 15) & 1;
  ll ans = (qpow(mod - 2, K + 1, mod) - 1 + mod) % mod * inv3 % mod;

  if (odd == false) ans = (mod - ans) % mod;
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // bf();

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
