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

const int N = 1e6 + 10;
ll fac[N], inv[N];
ll C(int n, int m) {
  return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return res;
}
ll g[N];

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
  pair<m32, m32> sqrt() const {
#ifdef CIPOLLA
    return cipolla(v);
#else
    return {1, 1};
#endif
  }
  friend ostream &operator<<(ostream &os, const m32<mod> &m) {
    return os << m.v;
  }
  friend istream &operator>>(istream &is, m32<mod> &m) {
    return is >> m.v;
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
  int t = f.deg() + g.deg() - 1;
  return mul(f, g, get_lim(t)).cut(t);
}

void solve() {
  int n; cin >> n;
  for (int i = 0; i * 3 <= n; i++) {
    g[i] = C(n - 2 * i, i) * qpow(26, n - 3 * i, mod) % mod;
  }
  Poly F(n + 1), G(n + 1);
  for (int i = 0; i <= n; i++) {
    G[n - i] = fac[i] * g[i] % mod;
    if (i & 1) {
      F[i] = mod - inv[i];
    } else {
      F[i] = inv[i];
    }
  }
  auto S = F * G;
  for (int i = 0; i <= n; i++) {
    mint ans = S[n - i] * inv[i];
    cout << ans << " \n"[i == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  fac[0] = fac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = inv[mod % i] * (mod - mod / i) % mod;
  }
  for (int i = 2; i < N; i++) {
    inv[i] = inv[i] * inv[i - 1] % mod;
  }

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
