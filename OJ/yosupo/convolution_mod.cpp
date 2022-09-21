#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

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

template <typename T> struct NumberTheoreticTransform {
  static int max_base;
  static T root;
  static vector<T> r, ir;

  NumberTheoreticTransform() {}

  static void init() {
    if (!r.empty()) return;
    int mod = T::get_mod();
    int tmp = mod - 1;
    root = 2;
    while (root.pow(tmp >> 1) == 1) root += 1;
    max_base = 0;
    while (~tmp & 1) tmp >>= 1, max_base += 1;
    r.resize(max_base), ir.resize(max_base);
    for (int i = 0; i < max_base; i++) {
      r[i] = - root.pow((mod - 1) >> (i + 2));
      ir[i] = r[i].inv();
    }
  }
  static void ntt(vector<T> &a) {
    init();
    int n = (int) a.size();
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
    int n = (int) a.size();
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
    for (auto &x : a) x *= iv;
  }
  static vector<T> convolution(vector<T> a, vector<T> b) {
    int k = (int) a.size() + (int) b.size() - 1, n = 1;
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

using NTT = NumberTheoreticTransform<mint>;
using fps = vector<mint>;

void solve() {
  int n, m; cin >> n >> m;
  fps a(n), b(m);
  for (auto &&x : a) cin >> x;
  for (auto &&x : b) cin >> x;

  const fps c = NTT::convolution(a, b);
  for (auto &&x : c) cout << x << ' ';
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
