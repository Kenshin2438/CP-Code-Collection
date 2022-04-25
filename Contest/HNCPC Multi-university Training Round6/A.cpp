#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

const int mod = (int) 1e9 + 7;
const int num = 50847534;

ll qpow(ll x, ll n, ll mod) {
  ll res = 1;
  for (x %= mod; n > 0; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}

map<int, ll> E;

ll sol(int x) {
  if (E.count(x)) return E[x];
  auto &res = E[x];
  int _ = x;
  vec<int> p;
  for (ll i = 2; i * i <= x; i ++)
    if (x % i == 0) {
      p.push_back(i);
      while (x % i == 0) x /= i;
    }
  if (x != 1) p.push_back(x);

  res = num;
  for (int pi : p) res = (res + sol(_ / pi)) % mod;
  return res = res * qpow(SZ(p), mod - 2, mod) % mod;
}

void SingleTest(int TestCase) {
  int x; cin >> x;
  E[1] = 0;
  cout << sol(x) << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
