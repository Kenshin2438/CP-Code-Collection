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

template <uint32_t mod> struct m32 {
  static_assert(mod < (1U << 31), "Modulus error!");

  using u32 = uint32_t;
  using u64 = uint64_t;
  using i64 = int64_t;

  u32 v = 0;
  template <typename T> u32 norm(T v) {
    return static_cast<u32>((v %= mod) < 0 ? mod + v : v);
  }
  m32() = default;
  template <typename T> m32(T _ = 0) : v(norm(_)) {}
  ~m32() = default;

  m32 &operator=(const int &rhs) { return v = norm(rhs), *this; }
  m32 operator-() const {
    return v == 0 ? m32(0) : m32(mod - v);
  }
  m32 &operator+=(const m32 &rhs) {
    v += rhs.v;
    if (v >= mod) v -= mod;
    return *this;
  }
  m32 &operator-=(const m32 &rhs) {
    if (v < rhs.v) v += mod;
    v -= rhs.v;
    return *this;
  }
  m32 &operator*=(const m32 &rhs) {
    v = (u64)v * rhs.v % mod;
    return *this;
  }
  m32 &operator/=(const m32 &rhs) {
    return *this *= rhs.inv();
  }
  m32 operator+(const m32 &rhs) const { return m32(*this) += rhs; }
  m32 operator-(const m32 &rhs) const { return m32(*this) -= rhs; }
  m32 operator*(const m32 &rhs) const { return m32(*this) *= rhs; }
  m32 operator/(const m32 &rhs) const { return m32(*this) /= rhs; }
  bool operator==(const m32 &rhs) const { return rhs.v == v; }
  bool operator!=(const m32 &rhs) const { return rhs.v != v; }
  m32 pow(i64 n) const {
    m32 x(*this), res(1);
    for (; n > 0; n >>= 1, x *= x) {
      if (n & 1LL) res *= x;
    }
    return res;
  }
  m32 inv() const {
    assert(v != 0);
    return pow(mod - 2);
  }

  static u32 get_mod() { return mod; }
  friend ostream &operator<<(ostream &os, const m32 &m) {
    return os << m.v;
  }
  friend istream &operator>>(istream &is, m32 &m) {
    long long a;
    is >> a;
    m = m32<mod>(a);
    return is;
  }
};
const int mod = 998244353;
using mint = m32<mod>;

template <typename T> T ModSqrt(T a) {
  const int p = T::get_mod();
  // Tonelli-Shanks
  if (a == 0 || p <= 2) return a;
  if (a.pow((p - 1) / 2) != 1) return -1;
  if (p % 4 == 3) return a.pow((p + 1) / 4);
  int k = __builtin_ctz(p - 1), h = (p - 1) >> k;
  T N = 2; while (N.pow((p - 1) / 2) == 1) N += 1;
  T x = a.pow((h + 1) / 2), g = N.pow(h), b = a.pow(h);
  for (int m = 0;; k = m) {
    T t = b;
    for (m = 0; m < k && t != 1; m++) t *= t;
    if (m == 0) return x;
    T gs = g.pow(1 << (k - m - 1));
    g = gs * gs, b *= g, x *= gs;
  }
  return -1;
}

template <typename T> struct NumberTheoreticTransform {
  static int max_base;
  static T root;
  static vector<T> r, ir;

  NumberTheoreticTransform() {}

  static void init() {
    if (!r.empty()) return;
    const int tmp = T::get_mod() - 1;
    for (root = 2; root.pow(tmp >> 1) == 1; root += 1);
    max_base = __builtin_ctz(tmp);
    r.resize(max_base), ir.resize(max_base);
    for (int i = 0; i < max_base; i++) {
      r[i] = -root.pow(tmp >> (i + 2));
      ir[i] = r[i].inv();
    }
  }
  static void ntt(vector<T> &a) {
    init();
    const int n = a.size();
    assert((n & (n - 1)) == 0);
    assert(n <= (1 << max_base));
    for (int k = n; k >>= 1;) {
      T w = 1;
      for (int s = 0, t = 0; s < n; s += 2 * k) {
        for (int i = s, j = s + k; i < s + k; i++, j++) {
          T x = a[i], y = w * a[j];
          a[i] = x + y, a[j] = x - y;
        }
        w *= r[__builtin_ctz(++ t)];
      }
    }
  }
  static void intt(vector<T> &a) {
    init();
    const int n = a.size();
    assert((n & (n - 1)) == 0);
    assert(n <= (1 << max_base));
    for (int k = 1; k < n; k <<= 1) {
      T w = 1;
      for (int s = 0, t = 0; s < n; s += 2 * k) {
        for (int i = s, j = s + k; i < s + k; i++, j++) {
          T x = a[i], y = a[j];
          a[i] = x + y, a[j] = (x - y) * w;
        }
        w *= ir[__builtin_ctz(++ t)];
      }
    }
    T iv = T(n).inv();
    for (auto &&x : a) x *= iv;
  }
  template <class F> static F convolution(F a, F b) {
    const int k = (int) a.size() + (int) b.size() - 1;
    int n = 1;
    while (n < k) n <<= 1;
    a.resize(n), b.resize(n);
    ntt(a), ntt(b);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    intt(a), a.resize(k);
    return a;
  }
};
template <typename T> int NumberTheoreticTransform<T>::max_base = 0;
template <typename T> T NumberTheoreticTransform<T>::root = T();
template <typename T> vector<T> NumberTheoreticTransform<T>::r  = vector<T>();
template <typename T> vector<T> NumberTheoreticTransform<T>::ir = vector<T>();
// using NTT = NumberTheoreticTransform<mint>;

template <typename T> struct FormalPowerSeries : vector<T> {
  using NTT = NumberTheoreticTransform<T>;
  using vector<T>::vector;
  using vector<T>::operator=;
  using F = FormalPowerSeries;

  FormalPowerSeries(const vector<T> &v) : vector<T>(v) {}

  F pre(int d) const {
    const int n = this->size();
    return F(this->begin(), this->begin() + min(n, d));
  }
  F rev(int deg = -1) const {
    F res(*this);
    if (deg != -1) res.resize(deg, 0);
    reverse(res.begin(), res.end());
    return res;
  }
  void shrink() {
    while (!this->empty() && this->back() == 0) this->pop_back();
  }

  F operator-() const {
    F res(*this);
    for (auto &&x : res) x = -x;
    return res;
  }
  F &operator+=(const T &rhs) {
    if (this->empty()) this->resize(1, 0);
    (*this)[0] += rhs;
    return *this;
  }
  F &operator-=(const T &rhs) {
    if (this->empty()) this->resize(1, 0);
    (*this)[0] -= rhs;
    return *this;
  }
  F &operator*=(const T &rhs) {
    for (auto &&x : *this) x *= rhs;
    return *this;
  }
  F &operator/=(const T &rhs) {
    assert(rhs != T(0));
    return *this *= rhs.inv();
  }
  F &operator+=(const F &v) {
    if (v.size() > this->size()) this->resize(v.size());
    for (int i = 0; i < (int) v.size(); i++) (*this)[i] += v[i];
    this->shrink();
    return *this;
  }
  F &operator-=(const F &v) {
    if (v.size() > this->size()) this->resize(v.size());
    for (int i = 0; i < (int) v.size(); i++) (*this)[i] -= v[i];
    this->shrink();
    return *this;
  }
  F &operator*=(const F &v) {
    if (this->empty() || v.empty()) {
      this->clear();
      return *this;
    }
    return *this = NTT::convolution(*this, v);
  }
  F &operator/=(const F &v) {
    if (v.size() > this->size()) {
      this->clear();
      return *this;
    }
    const int n = this->size() - (int) v.size() + 1;
    return *this = (rev() * v.rev().inv(n)).pre(n).rev();
  }
  F &operator%=(const F &v) {
    return *this -= (*this / v) * v;
  }
  F &operator<<=(const int &d) {
    this->insert(this->begin(), d, 0);
    return *this;
  }
  F &operator>>=(const int &d) {
    const int n = this->size();
    this->erase(this->begin(), this->begin() + min(n, d));
    return *this;
  }

  F operator+(const T &x) const { return F(*this) += x; }
  F operator-(const T &x) const { return F(*this) -= x; }
  F operator*(const T &x) const { return F(*this) *= x; }
  F operator/(const T &x) const { return F(*this) /= x; }
  F operator+(const F &v) const { return F(*this) += v; }
  F operator-(const F &v) const { return F(*this) -= v; }
  F operator*(const F &v) const { return F(*this) *= v; }
  F operator/(const F &v) const { return F(*this) /= v; }
  F operator%(const F &v) const { return F(*this) %= v; }
  F operator<<(int d) const { return F(*this) <<= d; }
  F operator>>(int d) const { return F(*this) >>= d; }

  T eval(const T &x) const {
    T res = 0;
    for (int i = (int) this->size() - 1; i >= 0; i--) {
      res *= x, res += (*this)[i];
    }
    return res;
  }
  F deriv() const {
    if (this->empty()) return *this;
    const int n = this->size();
    F res(n - 1);
    for (int i = 1; i < n; i++) {
      res[i - 1] = (*this)[i] * i;
    }
    return res;
  }
  F integral() const {
    if (this->empty()) return *this;
    const int n = this->size();
    F res(n + 1);
    for (int i = 0; i < n; i++) {
      res[i + 1] = (*this)[i] / (i + 1);
    }
    return res;
  }

  // O(n log n)
  F inv(int deg = -1) const {
    assert(!this->empty() && (*this)[0] != 0);
    if (deg == -1) deg = this->size();
    F res(1, (*this)[0].inv());
    for (int m = 1; m < deg; m <<= 1) {
      F f = pre(2 * m), g = res;
      f.resize(2 * m), NTT::ntt(f);
      g.resize(2 * m), NTT::ntt(g);
      for (int i = 0; i < 2 * m; i++) f[i] *= g[i];
      NTT::intt(f);
      for (int i = 0; i < m; i++) f[i] = 0;
      NTT::ntt(f);
      for (int i = 0; i < 2 * m; i++) f[i] *= g[i];
      NTT::intt(f);
      for (int i = 0; i < m; i++) f[i] = 0;
      res -= f;
    }
    res.resize(deg);
    return res;
  }

  // O(n log n)
  F log(int deg = -1) const {
    assert((*this)[0] == 1);
    if (deg == -1) deg = this->size();
    F res = (deriv() * inv(deg)).pre(deg - 1).integral();
    res.resize(deg);
    return res;
  }

  // F exp(int deg = -1) const {
  //   assert((*this)[0] == 0);
  //   if (deg == -1) deg = this->size();
  //   F res(1, 1), g = res;
  //   for (int m = 1; m < deg; m <<= 1) {
  //     g = (g + g - g * g * res).pre(m);
  //     F a = pre(m).deriv();
  //     F b = (a + g * (res.deriv() - res * a)).pre(2 * m - 1);
  //     res = (res + res * (pre(2 * m) - b.integral())).pre(2 * m);
  //   }
  //   res.resize(deg);
  //   return res;
  // }
  F exp(int deg = -1) const {
    assert((*this)[0] == 0);
    if (deg == -1) deg = this->size();
    vector<T> inv(2 * deg + 1, 0);
    inv[1] = 1;
    int mod = T::get_mod();
    for (int i = 2; i <= 2 * deg; i++) {
      inv[i] = -inv[mod % i] * T(mod / i);
    }

    auto inplace_integral = [inv](F &f) {
      if (f.empty()) return;
      int n = f.size();
      f.insert(begin(f), 0);
      for (int i = 1; i <= n; i++) f[i] *= inv[i];
    };

    auto inplace_derivative = [](F &f) {
      if (f.empty()) return;
      int n = f.size();
      f.erase(begin(f));
      for (int i = 0; i < n - 1; i++) f[i] *= T(i + 1);
    };

    F ret{1, this->size() > 1 ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};
    for (int m = 2; m < deg; m <<= 1) {
      auto y = ret; y.resize(2 * m);
      NTT::ntt(y);
      z1 = z2;
      F z(m);
      for (int i = 0; i < m; i++) z[i] = y[i] * z1[i];
      NTT::intt(z);
      fill(begin(z), begin(z) + m / 2, 0);
      NTT::ntt(z);
      for (int i = 0; i < m; i++) z[i] *= -z1[i];
      NTT::intt(z);
      c.insert(end(c), begin(z) + m / 2, end(z));
      z2 = c, z2.resize(2 * m);
      NTT::ntt(z2);
      F x(begin(*this), begin(*this) + min((int)this->size(), m));
      inplace_derivative(x);
      x.resize(m, 0);
      NTT::ntt(x);
      for (int i = 0; i < m; i++) x[i] *= y[i];
      NTT::intt(x);
      x -= ret.deriv(), x.resize(2 * m);
      for (int i = 0; i < m - 1; i++) x[m + i] = x[i], x[i] = 0;
      NTT::ntt(x);
      for (int i = 0; i < 2 * m; i++) x[i] *= z2[i];
      NTT::intt(x);
      x.pop_back();
      inplace_integral(x);
      for (int i = m; i < min((int)this->size(), 2 * m); i++)
        x[i] += (*this)[i];
      fill(begin(x), begin(x) + m, 0);
      NTT::ntt(x);
      for (int i = 0; i < 2 * m; i++) x[i] *= y[i];
      NTT::intt(x);
      ret.insert(end(ret), begin(x) + m, end(x));
    }
    ret.resize(deg);
    return ret;
  }

  // O(n log k)
  F pow(long long k, int deg = -1) const {
    if (deg == -1) deg = this->size();
    const int n = this->size();
    if (k == 0) {
      F res(deg);
      if (deg > 0) res[0] = 1;
      return res;
    }
    for (int i = 0; i < n; i++) {
      if ((*this)[i] == 0) continue;
      if (i > (deg - 1) / k) return F(deg);
      const T &val = (*this)[i];
      F res = (((*this >> i) / val).log(deg - i * k) * T(k)).exp() * val.pow(k);
      res.insert(res.begin(), i * k, 0);
      return res;
    }
    return F(deg);
  }

  // O(n log n)
  F sqrt(int deg = -1) const {
    if (deg == -1) deg = this->size();
    const int mod = T::get_mod();
    if ((*this)[0] == 0) {
      for (int i = 1; i < (int)this->size(); i++) {
        if ((*this)[i] != 0) {
          if (i & 1) return {};
          if ((*this)[i].pow((mod - 1) / 2) != 1) return {};
          if (deg <= i / 2) break;
          return ((*this) >> i).sqrt(deg - i / 2) << (i / 2);
        }
      }
      return F(deg);
    }
    if ((*this)[0].pow((mod - 1) / 2) != 1) return {};
    static const T inv2 = T(2).inv();
    F ret(1, ModSqrt((*this)[0]));
    for (int m = 1; m < deg; m <<= 1) {
      F g = (*this).pre(m * 2) * ret.inv(m * 2);
      g.resize(2 * m);
      ret = (ret + g) * inv2;
    }
    ret.resize(deg);
    return ret;
  }
  F sqrt_norm(int deg = -1) const {
    F A = sqrt(deg), B = -A;
    if (A[0].v < B[0].v) return A;
    return B;
  };
};
using fps = FormalPowerSeries<mint>;

void solve() {
  int n, k; cin >> n >> k;
  fps f(n + 1);
  for (auto &&x : f) cin >> x;
  auto g = ((f - f.sqrt_norm().inv().integral().exp() + (mint(2) - f[0])).log() + 1).pow(k).deriv();
  g.pop_back();
  for (const auto &x : g) cout << x << ' ';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
