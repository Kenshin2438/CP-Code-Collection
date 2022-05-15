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
  int v = 0, iv = 0;
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
    if (n == 0) return 1;
    m32 res(1);
    for (m32 x = *this; n > 0; n >>= 1, x *= x) {
      if (n & 1) res *= x;
    }
    return res;
  }
  m32 inv() {
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
const int mod = 998244353, g = 3, ig = 332748118;
using mint = m32<mod>;

struct poly : vec<mint> {
  
};

void SingleTest(int TestCase) {
  str a, b; cin >> a >> b;
  int k; cin >> k;
  int n = a.length(), m = b.length();
  if (n < m) return cout << "0\n", void();
  reverse(all(b)); // 反序后可卷积

  for (int _ = 0; _ < 26; _ ++) {
    char ch = 'a' + _;
    poly A(n), B(m);
    for (int i = 0; i < n; i++) A[i] = a[i] == ch;
    for (int i = 0; i < m; i++) B[i] = b[i] == ch;
    // vec<int> C = NTT(A, B);
    for (int i = 0; i <= n - m; i ++) {

    }
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
