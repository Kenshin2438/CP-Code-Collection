#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

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
  m32 &operator/=(const m32 &rhs) { return *this *= rhs.inv(); }
  m32 operator+(const m32 &rhs) const { return m32(*this) += rhs; }
  m32 operator-(const m32 &rhs) const { return m32(*this) -= rhs; }
  m32 operator*(const m32 &rhs) const { return m32(*this) *= rhs; }
  m32 operator/(const m32 &rhs) const { return m32(*this) /= rhs; }
  bool operator==(const m32 &rhs) const { return rhs.v == v; }
  bool operator!=(const m32 &rhs) const { return rhs.v != v; }
  m32 pow(i64 n) const {
    m32 x(*this), res(1);
    for (; n > 0; n >>= 1, x *= x)
      if (n & 1LL) res *= x;
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
    long long a; is >> a; m = m32<mod>(a);
    return is;
  }
};

const int mod = 998244353;
using mint = m32<mod>;

template <typename T> struct Combination {
  int n; vector<T> facs, ifacs, invs;

  inline void extend() {
    int m = n << 1;
    facs.resize(m), ifacs.resize(m), invs.resize(m);
    for (int i = n; i < m; i++) facs[i] = facs[i - 1] * i;
    ifacs[m - 1] = T(1) / facs[m - 1];
    invs[m - 1] = facs[m - 2] * ifacs[m - 1];
    for (int i = m - 2; i >= n; i--) {
      ifacs[i]= ifacs[i + 1] * (i + 1);
      invs[i] = ifacs[i] * facs[i - 1];
    }
    n = m;
  }

  Combination(int MAX = 0)
    : n(1), facs(1, T(1)), ifacs(1, T(1)), invs(1, T(1)) {
    while (n <= MAX) extend();
  }

  T fac(int i) {
    assert(i >= 0);
    while (n <= i) extend();
    return facs[i];
  }
  T ifac(int i) {
    assert(i >= 0);
    while (n <= i) extend();
    return ifacs[i];
  }
  T inv(int i) {
    assert(i >= 0);
    while (n <= i) extend();
    return invs[i];
  }

  T C(int n, int r) {
    if (n < 0 || n < r || r < 0) return T(0);
    return fac(n) * ifac(r) * ifac(n - r);
  }
  T P(int n, int r) {
    if (n < 0 || n < r || r < 0) return T(0);
    return fac(n) * ifac(n - r);
  }
  T S2(int n, int k) {
    T res(0);
    for (int i = 0; i <= k; i++) {
      T t = T(k - i).pow(n) * C(k, i);
      (i & 1) ? res -= t : res += t;
    }
    return res * ifac(k);
  }
  T B(int n, int k) { // sum_{i=0}^{k} S2(n, i)
    static vector<T> sum = { 1 };
    for (static int i = 1; i <= k; i++) {
      sum.push_back(sum.back() + (i & 1 ? -ifac(i) : ifac(i)));
    }
    T res(0);
    for (int i = 1; i <= k; i++) {
      res += sum[k - i] * T(i).pow(n) * ifac(i);
    }
    return res;
  }
};
Combination<mint> comb;

void solve() {
  int n; cin >> n;
  mint ans = 1;
  for (int i = 0; i < n / 3; i++) {
    vector<int> e(3);
    cin >> e[0] >> e[1] >> e[2];
    sort(all(e));

    if (e[0] == e[1] && e[1] == e[2]) {
      ans *= 3;
    } else if (e[1] == e[0]) {
      ans *= 2;
    } 
  }
  cout << ans * comb.C(n / 3, n / 6) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}