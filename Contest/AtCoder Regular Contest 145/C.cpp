#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int mod = 998244353;
const int N = 4e5 + 10;

ll fac[N], inv[N], ifac[N];

ll C(int n, int m) {
  return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return res;
}
ll INV(ll x) { return x == 1 ? x : (mod - mod / x) * INV(mod % x) % mod; }

void solve() {
  int n; cin >> n;
  cout << INV(n + 1) * qpow(2, n, mod) % mod * C(2 * n, n) % mod * fac[n] % mod << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  fac[0] = fac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = inv[mod % i] * (mod - mod / i) % mod;
  }
  ifac[0]= ifac[1] = 1;
  for (int i = 2; i < N; i++) {
    ifac[i] = ifac[i - 1] * inv[i] % mod;
  }

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
