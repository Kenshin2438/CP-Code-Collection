#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

/**
1
1000000000000
1099683734530790325
**/

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

const ll mod = 29LL << 57 | 1LL;
ll add(ll a, ll b) { return a += b, (a >= mod ? a - mod : a); }
ll sub(ll a, ll b) { return a -= b, (a < 0 ? a + mod : a); }
ll mul(ll a, ll b) {
  // 利用溢出机制 (a * b) \equiv ((a / mod) * b * mod) + R \pmod{2^64}
  return (a * b - ull((long double)a / mod * b) * mod + mod) % mod;
}
ll inv(ll x) { return x == 1LL ? x : mul(inv(mod % x), mod - mod / x); }
const ll iv2 = inv(2);
ll G(ll x) { return mul(iv2, mul(x, x + 1)); }
ll H(ll pe, ll e) { return mul(pe, sub(inv(e), inv(e - 1))); }

ll PN(int id, ll n, ll h) {
  ll res = mul(G(n), h);
  for (int i = id; i < (int)p.size(); i++) {
    ll val = n / p[i], pe = p[i], e = 1;
    if (val < p[i]) break;
    while (val >= p[i]) {
      val /= p[i], pe *= p[i], e += 1;
      res = add(res, PN(i + 1, val, mul(H(pe, e), h)));
    }
  }
  return res;
}

void solve() {
  ll N; cin >> N;
  cout << mul(inv(N), PN(0, N, 1)) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init();

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
