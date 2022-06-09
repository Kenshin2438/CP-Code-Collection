#include <bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937 rng(__builtin_ia32_rdtsc());
inline ll randint(ll l, ll r) {
  return uniform_int_distribution<ll>(l, r)(rng);
}

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n > 0LL; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}

struct R {
  ll a, p, x, y, z;

  R(ll _a, ll _p) : a(_a), p(_p) { x = 1LL, y = 0LL, z = 0LL; }
  void rand() {
    x = randint(0, p - 1);
    y = randint(0, p - 1);
    z = randint(0, p - 1);
  }
  R &operator*=(const R &rhs) {
    ll _x = (x * rhs.x + y * rhs.z % p * a + z * rhs.y % p * a) % p;
    ll _y = (x * rhs.y + y * rhs.x + z * rhs.z % p * a) % p;
    ll _z = (x * rhs.z + y * rhs.y + z * rhs.x) % p;
    x = _x, y = _y, z = _z;
    return *this;
  }

  void pow(ll n) {
    R res(a, p), b = *this;
    for (; n; n >>= 1, b *= b) {
      if (n & 1LL) res *= b;
    }
    x = res.x, y = res.y, z = res.z;
  }
};

ll Peralta_Method_Extension(ll a, ll p) {
  a = (a % p + p) % p;
  if (a == 0) return 0LL;

  if (p % 3 == 2) return qpow(a, (p * 2 - 1) / 3, p);
  
  if (qpow(a, (p - 1) / 3, p) != 1LL) return 0LL;
  // No Solution

  R t(a, p);
  while (true) {
    t.rand(), t.pow((p - 1) / 3);
    if (t.x == 0 && t.y != 0 && t.z == 0) {
      return qpow(t.y, p - 2, p);
    }
  }

  assert(false);
  return -1;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T;
  cin >> T;

  while (T--) {
    ll p, a;
    cin >> a >> p;

    cout << Peralta_Method_Extension(a, p) << '\n';
  }

  return 0;
}