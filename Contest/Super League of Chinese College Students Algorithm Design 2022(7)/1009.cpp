#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int mod = 1e9 + 7;

vector<int> p;
void init() {
  bitset<1000005> ntp;
  for (int i = 2; i < 1e6; i++) {
    if (ntp[i] == 0) p.emplace_back(i);
    for (const int &pr : p) {
      if (pr * 1LL * i >= 1e6) break;
      ntp[pr * i] = 1;
      if (i % pr == 0) break;
    }
  }
}

using ull = unsigned long long;
ll add(ll a, ll b) { return a += b, (a >= mod ? a - mod : a); }
ll sub(ll a, ll b) { return a -= b, (a < 0 ? a + mod : a); }
ll mul(ll a, ll b) {
  // 利用溢出机制 (a * b) \equiv ((a / mod) * b * mod) + R \pmod{2^64}
  return (a * b - ull((long double)a / mod * b) * mod + mod) % mod;
}
ll qpow(ll x, ll n) {
  ll res = 1;
  for (; n > 0; n >>= 1, x = mul(x, x)) {
    if (n & 1LL) res = mul(res, x);
  }
  return res;
}
ll inv(ll x) { return x == 1LL ? x : mul(inv(mod % x), mod - mod / x); }
const ll iv2 = inv(2);
ll G(ll x) { return mul(iv2, mul(x, x + 1)); }

void solve() {
  int n, m; cin >> n >> m;
  ll ans = 0;
  for (int i = 1; i <= m; i++) {
    int bn = m / i;
    ll val = bn == 1 ? n : mul(inv(bn - 1), qpow(bn, n) - 1);
    ans = add(ans, val);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
