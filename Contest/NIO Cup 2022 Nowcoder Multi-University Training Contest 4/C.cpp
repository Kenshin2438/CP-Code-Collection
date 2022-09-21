#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int P = 998244353;
int qpow(ll a, ll b = P - 2, ll m = P) {
  ll ret = m != 1;
  for (; b; b >>= 1) {
    if (b & 1) ret = ret * a % m;
    a = a * a % m;  
  }
  return ret;
}

struct m32 {
  int v = 0;
  m32(int _v = 0) { v = _v; }
  m32 &operator=(const int &m) {
    v = m;
    return *this;
  }
  m32 &operator+=(const m32 &m) {
    v = (v += m.v) >= P ? v - P : v;
    return *this;
  }
  m32 &operator-=(const m32 &m) {
    v = (v -= m.v) < 0 ? v + P : v;
    return *this;
  }
  m32 operator-() const { return v == 0 ? 0 : P - v; }
  m32 &operator*=(const m32 &m) {
    v = ll(v) * m.v % P;
    return *this;
  }
  m32 operator+(const m32 &m) const { return m32(*this) += m; }
  m32 operator-(const m32 &m) const { return m32(*this) -= m; }
  m32 operator*(const m32 &m) const { return m32(*this) *= m; }
  m32 inv() const { return qpow(v); }
  m32 pow(int n) const { return qpow(v, n, P); }
};

string to_string(const m32 &x) {
  return to_string(x.v);
}

inline int get_lim(int n) {
  int m = 1;
  while (m < n) m *= 2;
  return m;
}

struct Poly : std::vector<m32> {
  using vector::vector;
  bool isNTT = false;
  Poly(Poly::const_iterator pi, int len) : Poly(pi, pi + len) {}
  Poly rev() const { return Poly(rbegin(), rend()); }
  int deg() const { return size(); }
  Poly cut(int m) const { return Poly(begin(), begin() + min(deg(), m)); }
  Poly &resize(int m) {
    vector::resize(m);
    return *this;
  }
  Poly &fillZeroL(int t) {
    fill_n(begin(), t / 2, 0);
    return *this;
  }
  Poly &fillZeroH(int t) {
    fill_n(begin() + t / 2, t / 2, 0);
    return *this;
  }
  friend Poly operator+(Poly f, Poly g);
  friend Poly operator-(Poly f, Poly g);
  friend Poly operator*(Poly f, Poly g);
  Poly &ntt(int m);
  Poly &nttD(int m);
  Poly &intt(int m);
  Poly &invD(Poly f2, Poly nx, int t);
  Poly inv() const;
  Poly div(Poly g) const;
  Poly deriv() const;
  Poly integr() const;
  Poly ln() const;
  Poly exp() const;
  Poly sqrt() const;
  Poly pow(int k) const;
  Poly mod() const;
};

Poly w, Inv;

void pre_w(int n, int w0 = 3) {
  static int lim = (w = {1, 1}, 2);
  n = get_lim(n);
  if (n <= lim) return;
  w.resize(n);
  for (int l = lim; l < n; l *= 2) {
    m32 p = m32(w0).pow((P - 1) / l / 2);
    for (int i = 0; i < l; i += 2) {
      w[(l + i)] = w[(l + i) / 2];
      w[l + i + 1] = w[l + i] * p;
    }
  }
  lim = n;
}

void pre_inv(int n) {
  static int LIM = (Inv = {1, 1}, 2);
  if (n <= LIM) return;
  Inv.resize(n);
  for (int i = LIM; i < n; i++) {
    Inv[i] = Inv[P % i] * (P - P / i);
  }
  LIM = n;
}

static int ntt_size = 0;

void ntt(Poly::iterator f, int deg) {
  pre_w(deg);
  ntt_size += deg;
  for (int l = deg >> 1; l; l >>= 1)
    for (auto fi = f; fi - f < deg; fi += l * 2)
      for (int j = 0; j < l; j++) {
        auto x = fi[j] + fi[j + l];
        fi[j + l] = w[j + l] * (fi[j] - fi[j + l]);
        fi[j] = x;
      }
}

void intt(Poly::iterator f, int deg) {
  ntt_size += deg;
  for (int l = 1; l < deg; l <<= 1)
    for (auto fi = f; fi - f < deg; fi += l * 2)
      for (int j = 0; j < l; j++) {
        auto x = fi[j], y = fi[j + l] * w[j + l];
        fi[j] = x + y, fi[j + l] = x - y;
      }
  const auto deg_inv = P - (P - 1) / deg;
  for (int i = 0; i < deg; i++) f[i] *= deg_inv;
  std::reverse(f + 1, f + deg);
}

void nttD(Poly::iterator f, int n) {
  std::copy_n(f, n, f + n);
  intt(f + n, n);
  for (int i = n; i < n * 2; i++) f[i] *= w[i];
  ntt(f + n, n);
}

Poly &Poly::ntt(int n) {
  if (!isNTT) {
    resize(n);
    ::ntt(begin(), n);
    isNTT = true;
  }
  return *this;
}

Poly &Poly::intt(int m) {
  ::intt(begin(), m);
  isNTT = false;
  return *this;
}

Poly &Poly::nttD(int n) {
  resize(n * 2);
  ::nttD(begin(), n);
  return *this;
}

Poly &mul(Poly &f, Poly &g, int t) {
  f.ntt(t), g.ntt(t);
  for (int i = 0; i < t; i++) f[i] *= g[i];
  return f.intt(t);
}

Poly operator*(Poly f, Poly g) {
  if (f.deg() < g.deg()) swap(f, g);
  int t = f.deg() + g.deg() - 1;
  return mul(f, g, get_lim(t)).cut(t);
}

Poly operator+(Poly f, Poly g) {
  if (f.deg() < g.deg()) std::swap(f, g);
  for (int i = 0; i < g.deg(); i++) f[i] += g[i];
  return f;
}

Poly operator-(Poly f, Poly g) {
  for (auto &i : g) i = -i;
  return std::move(f) + g;
}

m32 mulAt(const Poly f, const Poly g, int u) {
  int n = f.deg() - 1, m = g.deg() - 1;
  m32 ans = 0;
  for (int i = std::max(0, u - m); i <= std::min(u, n); i++)
    ans += f[i] * g[u - i];
  return ans;
}

Poly &Poly::invD(Poly f2, Poly nx, int t) {
  mul(f2, nx, t).fillZeroL(t);  // 6E
  mul(f2, nx, t);               // 4E
  resize(t);
  for (int i = t / 2; i < t; i++) (*this)[i] = -f2[i];
  return *this;
}

Poly Poly::inv() const {  // 10E
  Poly x = {front().inv()};
  if (deg() == 1) return x;
  int lim = get_lim(deg());
  for (int t = 2; t <= lim; t <<= 1) x.invD(cut(t), x.cut(t), t);
  return x.cut(deg());
}

Poly Poly::div(Poly f2) const {  // 13E
  if (deg() == 1) return {front() * f2[0].inv()};
  int t = get_lim(deg());
  Poly x = cut(t / 2), g = Poly(f2).resize(t / 2).inv();  // 10E
  Poly q = mul(x, g, t).cut(t / 2);                       // 6E
  mul(q, f2, t).fillZeroL(t);                             // 6E
  for (int i = t / 2; i < std::min(t, deg()); i++) q[i] -= (*this)[i];
  mul(q, g, t);  // 4E
  for (int i = t / 2; i < t; i++) x[i] = -q[i];
  return x.cut(deg());
}

const int N = 1e7 + 50005;

int fac[N], inv[N];

void init() {
  fac[0] = fac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++) {
    fac[i] = fac[i - 1] * 1LL * i % P;
    inv[i] = inv[P % i] * 1LL * (P - P / i) % P;
  }
  for (int i = 2; i < N; i++) {
    inv[i] = inv[i - 1] * 1LL * inv[i] % P;
  }
}

std::mt19937 rng(__builtin_ia32_rdtsc());
template <typename T>
inline T randint(T l, T r) {
  return std::uniform_int_distribution<T>(l, r)(rng);
}
template <typename E>
inline E randreal(E l, E r) {
  return std::uniform_real_distribution<E>(l, r)(rng);
}

void solve() {
  int w, S = 0;
  cin >> w;
  // w = 10;
  vector<Poly> F(1 << w), G(w + 1);
  for (int i = 0; i < w; i++) {
    int c; cin >> c, S += c;
    // int c = 5000;
    F[1 << i].resize(c);
    for (int j = 0; j < c; j++) {
      F[1 << i][j] = inv[j];
    }
  }
  F[0] = {1};
  for (int mask = 0; mask < (1 << w); mask++) {
    F[mask] = F[mask ^ (mask & -mask)] * F[(mask & -mask)];

    int cnt = w - __builtin_popcount(mask);
    G[cnt] = G[cnt] + F[mask];
  }
  int q; cin >> q;
  // int q = 300;
  while (q--) {
    int n; cin >> n;
    // int n = 1e7 - randint(1, 100000);
    if (n < S)
      cout << 0 << '\n';
    else {
      m32 ans = 0;
      for (int o = w, sgn = 1; o >= 0; o--, sgn = -sgn) {
        m32 x = 0, pw = m32(o).pow(n - min((int) G[o].size() - 1, n));
        // m32 get_exp(int p, int n) {
        //   return m32(p).pow(n) * inv[n];
        // }
        for (int i = min((int) G[o].size() - 1, n); i >= 0; i--) {
          x += G[o][i] * pw * inv[n - i], pw *= o;
        }
        if (sgn == -1) ans -= x;
        else ans += x;
      }
      ans *= fac[n];
      cout << ans.v << '\n';
    }
  }
}

int main() {
  clock_t SS = clock();
  cin.tie(nullptr)->sync_with_stdio(false);
  init();

  int T = 1;
  // cin >> T;
  while (T--) solve();

  clock_t TT = clock();
  debug(double(TT - SS) / CLOCKS_PER_SEC);
  return 0;
}
