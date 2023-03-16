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

ll Sn = 0;

void solve() {
  ll n; cin >> n;
  assert(1 <= n && n <= (int) 1e6);
  Sn += n;

  ll _p1, _p2; cin >> _p1 >> _p2;
  assert(0 <= _p1 && _p1 <= 100);
  assert(0 <= _p2 && _p2 <= 100);
  assert(_p1 + _p2 > 0);
  if (_p1 < _p2) swap(_p1, _p2);

  const mint p1 = mint(_p1) / 100;
  const mint p2 = mint(_p2) / 100;

  const function<pair<mint, mint> (int)> E = [&](int num) {
    if (num == 0) return make_pair(mint(0), mint(0));
    const auto &[nE12, nE21] = E(num - 1);
    // E12 + (p1-1)*E21 = p1*nE21 + num
    // (p2-1)*E12 + E21 = p2*nE12 + num
    return make_pair(
      ((p2*nE12+num)*(p1-1)-(p1*nE21+num))/((p2-1)*(p1-1)-1),
      ((p1*nE21+num)*(p2-1)-(p2*nE12+num))/((p1-1)*(p2-1)-1)
    );
  };
  cout << E(n).first << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  assert(1 <= T && T <= 10000);
  while (T--) solve();
  assert(1 <= Sn && Sn <= (int) 1e6);

  return 0;
}