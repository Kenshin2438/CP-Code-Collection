#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int mod = 998'244'353;
int inv(int x) {
  return x == 1 ? x : inv(mod % x) * 1LL * (mod - mod / x) % mod;
}
ll binom(int n, int m) {
  assert(m >= 0 && n >= m);
  ll res = 1;
  for (int i = 2; i <= m; i++) res = res * i % mod;
  res = inv(res);
  for (int i = n; i > n - m; i--) res = res * i % mod;
  return res;
}

ll qpow(ll x, ll n) {
  if (n == 0) return 1LL;
  if (n == 1) return x;
  ll part = qpow(x, n / 2);
  return part * part % mod * qpow(x, n % 2) % mod;
}

void solve() {
  int n; cin >> n;

  int a = 0, b = 0, c = 0, ok = 0;
  bool wb = true, bw = true;
  for (int i = 0; i < n; i++) {
    string s; cin >> s;

    if (s == "BB") a -= 1, ok = 1;
    if (s == "WW") a += 1, ok = 1;
    if (s == "??") a -= 1, b += 2, c += 1;
    if (s == "?B" || s == "B?") a -= 1, b += 1;
    if (s == "?W" || s == "W?") b += 1;

    if (s[0] == 'B' || s[1] == 'W') wb = false;
    if (s[0] == 'W' || s[1] == 'B') bw = false;
  }

  if (b + a < 0 || a > 0) return cout << "0\n", void();
  ll ans = binom(b, -a);
  if (ok == 0) ans -= qpow(2, c);
  if (wb) ans += 1;
  if (bw) ans += 1;
  ans = (ans % mod + mod) % mod;
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
