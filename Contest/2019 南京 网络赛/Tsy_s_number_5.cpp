#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n > 0LL; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}
ll inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }

// 一般 O(log p); 最坏 O(log^2 p);
ll Tonelli_Shanks(ll a, ll p) {
  a = (a % p + p) % p;
  if (a == 0) return 0LL;

  if (qpow(a, (p - 1) / 2, p) != 1LL) return -1LL;  // No Solution

  if (p % 4 == 3) return qpow(a, (p + 1) / 4, p);

  ll k = __builtin_ctzll(p - 1), h = p >> k, N = 2;
  // p = 1 + h * 2^k
  while (qpow(N, (p - 1) / 2, p) == 1) N++;
  // find a non-square mod p

  ll x = qpow(a, (h + 1) / 2, p);
  ll g = qpow(N, h, p);
  ll b = qpow(a, h, p);

  for (ll m = 0;; k = m) {
    ll t = b;
    for (m = 0; m < k && t != 1LL; m++) {
      t = t * t % p;
    }

    if (m == 0) return x;
    ll gs = qpow(g, 1 << (k - m - 1), p);

    g = gs * gs % p;
    b = b * g % p;
    x = x * gs % p;
  }

  assert(false);
  return -1;
}

#ifndef TONELLI_SHANKS
  #define TONELLI_SHANKS
#endif

const int mod = 998244353;
const int N = 1e5 + 10;

int phi[N];

void init() {
  vector<int> p;

  phi[1] = 1;
  for (int i = 2; i < N; i++) {
    if (phi[i] == 0) {
      phi[i] = i - 1;
      p.emplace_back(i);
    }
    for (const int &pr : p) {
      if (pr * 1LL * i >= N) break;
      if (i % pr == 0) {
        phi[pr * i] = phi[i] * 1LL * pr % mod;
        break;
      } else {
        phi[pr * i] = phi[i] * 1LL * (pr - 1) % mod;
      }
    }
  }
}

template <int mod>
struct m32 {
  int v = 0;
  mutable int iv = 0;

  template <typename T>
  int norm(T v) {
    return (v %= mod) < 0 ? (mod + v) : v;
  }

  m32() = default;
  template <typename T> m32(T _ = 0) { v = norm(_); }
  ~m32() = default;
  
  m32 operator-() const { return v ? m32(mod - v) : m32(0); }
  m32 &operator=(const int &m) { return v = norm(m), *this; }
  m32 &operator+=(const m32 &m) {
    v = (v += m.v) >= mod ? v - mod : v;
    return *this;
  }
  m32 &operator-=(const m32 &m) {
    v = (v -= m.v) < 0 ? v + mod : v;
    return *this;
  }
  m32 &operator*=(const m32 &m) {
    v = norm(v * 1LL * m.v);
    return *this;
  }
  m32 &operator/=(const m32 &m) {
    v = norm(v * 1LL * m.inv());
    return *this;
  }
  m32 operator+(const m32 &m) const { return m32(*this) += m; }
  m32 operator-(const m32 &m) const { return m32(*this) -= m; }
  m32 operator*(const m32 &m) const { return m32(*this) *= m; }
  m32 operator/(const m32 &m) const { return m32(*this) /= m; }
  bool operator==(const m32 &m) const { return m.v == v; }
  bool operator!=(const m32 &m) const { return m.v != v; }
  m32 pow(long long n) const {
    if (n < 0) return inv().pow(-n);
    if (n == 1) return *this;
    if (n == 0) return m32(1);
    if (v == 0) return m32(0);
    m32 res = pow(n >> 1);
    return res * res * pow(n % 2);
  }
  m32 inv() const {
    assert(v != 0);
    m32 res(iv);  // check current inv
    if (res * v == 1) return res;
    return m32(iv = pow(mod - 2).v);
  }
  m32 sqrt() const {
#ifdef TONELLI_SHANKS
    return Tonelli_Shanks(v, mod);
#else
    return 1;
#endif
  }
  friend ostream &operator<<(ostream &os, const m32<mod> &m) {
    return os << m.v;
  }
  friend istream &operator>>(istream &is, m32<mod> &m) {
    is >> m.v;
    m.v = norm(m.v);
    return is;
  }
  friend string to_string(const m32 &m) {
    return to_string(m.v);
  }
};
using mint = m32<mod>;

struct Poly : vector<mint> {
  using vector::vector;
  bool is_NTT = false;
  Poly(Poly::const_iterator it, int n) : Poly(it, it + n) {}
  int deg() const { return this->size(); }
  Poly cut(int n) const {
    return Poly(begin(), begin() + min(deg(), n));
  }
  friend Poly operator*(Poly f, Poly g);
  Poly &NTT(int n);
  Poly &INTT(int n);
};

Poly w = { 1, 1 };
int get_lim(int n) {
  int res = 1;
  while (res < n) res <<= 1;
  return res;
}
void pre_w(int n, int w0 = 3) {
  static int lim = 2;
  n = get_lim(n);
  if (n <= lim) return;
  w.resize(n);
  for (int l = lim; l < n; l <<= 1) {
    auto p = mint(w0).pow((mod - 1) / l / 2);
    for (int i = 0; i < l; i += 2) {
      w[l + i] = w[(l + i) / 2];
      w[l + i + 1] = w[l + i] * p;
    }
  }
}
void NTT(Poly::iterator f, int deg) {
  pre_w(deg);
  for (int l = deg >> 1; l; l >>= 1) {
    for (auto fi = f; fi - f < deg; fi += l * 2) {
      for (int j = 0; j < l; j++) {
        auto x = fi[j] + fi[j + l];
        fi[j + l] = w[j + l] * (fi[j] - fi[j + l]);
        fi[j] = x;
      }
    }
  }
}
void INTT(Poly::iterator f, int deg) {
  for (int l = 1; l < deg; l <<= 1) {
    for (auto fi = f; fi - f < deg; fi += l * 2) {
      for (int j = 0; j < l; j++) {
        auto x = fi[j], y = fi[j + l] * w[j + l];
        fi[j] = x + y, fi[j + l] = x - y;
      }
    }
  }
  const auto deg_inv = mod - (mod - 1) / deg;
  for (int i = 0; i < deg; i++) f[i] *= deg_inv;
  reverse(f + 1, f + deg);
}
Poly &Poly::NTT(int n) {
  if (is_NTT == false) {
    resize(n);
    ::NTT(begin(), n);
    is_NTT = true;
  } 
  return *this;  
}
Poly &Poly::INTT(int n) {
  ::INTT(begin(), n);
  is_NTT = false;
  return *this;
}
Poly &mul(Poly &f, Poly &g, int t) {
  f.NTT(t), g.NTT(t);
  for (int i = 0; i < t; i++) f[i] *= g[i];
  return f.INTT(t);
}

Poly operator*(Poly f, Poly g) {
  if (f.deg() < g.deg()) swap(f, g);
  int t = f.deg() + g.deg() + 1;
  return mul(f, g, get_lim(t)).cut(t);
}

void solve() {
  static const mint B = mint(2).sqrt();
  static const mint D = B.inv();

  debug(B);

  int n; cin >> n;
  
  Poly f(n + 1, 0);
  for (int i = 1; i <= n; i++) f[ phi[i] ] += 1;
  for (int i = 1; i <= n; i++) {
    f[i] *= D.pow(i * 1LL * i) * i;
  }

  auto h = f * f;
  mint ans = 0;
  for (int k = 2; k <= 2 * n; k++) {
    ans += h[k] * B.pow(k * 1LL * k);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  init();
  int T; cin >> T;
  while (T--) solve();

  return 0;
}