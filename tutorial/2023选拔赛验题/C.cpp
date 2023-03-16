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

const int mod = 1e9 + 7;
using mint = m32<mod>;

ll Sn = 0;

void solve() {
  int n; cin >> n;
  assert(1 <= n && n <= (int) 1e6);
  Sn += n;

  vector<pair<ll, ll>> p(n);
  for (auto &&[a, b] : p) {
    cin >> a >> b;
    assert(1 <= a && a <= (int) 1e9);
    assert(1 <= b && b <= (int) 1e9);
  }

  if (p[0].first == p[0].second) return cout << "0\n", void();

  vector<mint> dp{1, 1};
  for (int i = 1; i < n; i++) {
    vector<mint> ndp{0, 0};
    if (p[i].first != p[i - 1].second) ndp[0] += dp[0];
    if (p[i].first != p[i - 1].first) ndp[0] += dp[1];
    if (p[i].second != p[i - 1].second) ndp[1] += dp[0];
    if (p[i].second != p[i - 1].first) ndp[1] += dp[1];
    dp = move(ndp);
  }
  cout << dp[0] + dp[1] << "\n";
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