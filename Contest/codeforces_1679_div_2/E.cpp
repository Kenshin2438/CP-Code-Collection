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
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

template <int mod> struct m32 {
  int v = 0;
  mutable int iv = 0;
  m32(int _ = 0) : v(_ % mod) {
    if (v < 0) v += mod;
  }
  m32(ll _ = 0) : v(_ % mod) {
    if (v < 0) v += mod;
  }
  m32 operator-() const {
    return v ? mod - v : 0;
  }
  m32 &operator=(const int &m) {
    return this->v = m, *this;
  }
  m32 &operator+=(const m32 &m) {
    v = (v += m.v) >= mod ? v - mod : v;
    return *this;
  }
  m32 &operator-=(const m32 &m) {
    v = (v -= m.v) < 0 ? v + mod : v;
    return *this;
  }
  m32 &operator*=(const m32 &m) {
    v = ll(v) * m.v % mod;
    return *this;
  }
  m32 operator+(const m32 &m) const {
    return m32(*this) += m;
  }
  m32 operator-(const m32 &m) const {
    return m32(*this) -= m;
  }
  m32 operator*(const m32 &m) const {
    return m32(*this) *= m;
  }
  bool operator==(const m32 &m) const {
    return m.v == v;
  }
  bool operator!=(const m32 &m) const {
    return m.v != v;
  }
  m32 pow(int n) const {
    if (n < 0) return inv().pow(-n);
    // if (v == 0) return *this;
    m32 res(1);
    if (n == 0) return res;
    for (m32 x(this->v); n > 0; n >>= 1, x *= x) {
      if (n & 1) res *= x;
    }
    return res;
  }
  m32 inv() const {
    assert(v != 0);
    m32 res(iv);  // check current inv
    if (*this * res == 1) return res;
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
    is >> m.v;
    m.v %= mod;
    if (m.v < 0) m.v += mod;
    return is;
  }
};
using mint = m32<998244353>;

void SingleTest(int TestCase) {
  int n; cin >> n;
  str s; cin >> s;
  int m = count(all(s), '?');
  str t = "#"; for (char ch : s) t += ch, t += '#';
  vec<vec<mint>> dp(17 + 1, vec<mint>(1 << 17, 0));
  for (int i = 0; i < SZ(t); i++) {
    int cur = m, mask = 0;
    for (int len = 0; i + len < SZ(t) && len <= i; len++) {
      if (t[i + len] == '#') continue;
      if (t[i + len] == '?' && t[i - len] == '?') {
        cur -= (len != 0);
      } else if (t[i + len] != '?' && t[i - len] != '?') {
        if (t[i + len] != t[i - len]) break;
      } else {
        cur--, mask |= 1 << ((t[i + len] ^ t[i - len] ^ '?') - 'a');
      }
      for (int j = 1; j <= 17; j++) dp[j][mask] += mint(j).pow(cur);
    }
  }
  for (int i = 0; i < 17; i++) {
    for (int mask = 0; mask < SZ(dp[0]); mask++) {
      if (mask >> i & 1) for (int j = 1; j <= 17; j++) {
        dp[j][mask] += dp[j][mask ^ (1 << i)];
      }
    }
  }
  int q; cin >> q;
  for (str Q; q--; ) {
    cin >> Q;
    int mask = 0;
    for (char ch : Q) mask |= 1 << (ch - 'a');
    cout << dp[SZ(Q)][mask] << '\n';
  }
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
