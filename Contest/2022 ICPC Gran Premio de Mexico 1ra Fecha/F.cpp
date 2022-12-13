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

struct Matrix {
  int n; vector<vector<mint>> M;

  Matrix(int _n, bool id = false) : n(_n) {
    M.resize(n, vector<mint>(n));
    if (id) for (int i = 0; i < n; i++) M[i][i] = 1;
  }

  Matrix &operator*=(const Matrix &m) {
    vector<vector<mint>> ans(n, vector<mint>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          ans[i][j] += M[i][k] * m.M[k][j];
        }
      }
    }
    this->M = move(ans);
    return *this;
  }
  Matrix pow(int k) const {
    Matrix x(*this), res(n, true);
    for (; k > 0; k >>= 1, x *= x) {
      if (k & 1) res *= x;
    }
    return res;
  }
};

void solve() {
  int n, m; cin >> n >> m;
  vector<int> p(m);
  for (int &x : p) cin >> x;
  p.emplace_back(-1), p.emplace_back(n + 1);
  sort(all(p));
  mint ans = 1;

  Matrix Mat(2);
  Mat.M[0][0] = 1, Mat.M[0][1] = 1;
  Mat.M[1][0] = 1, Mat.M[1][1] = 0;
  const int N = 5e6 + 10;
  vector<mint> fib(N + 1); fib[0] = 0, fib[1] = 1;
  for (int i = 2; i <= N; i++) fib[i] = fib[i - 1] + fib[i - 2];
  const auto calc = [&](int len) -> mint {
    if (len <= N) return fib[len];
    const auto &PMat = Mat.pow(len - 1);
    return PMat.M[0][0];
  };
  for (int i = 1; i < sz(p); i++) {
    int len = p[i] - p[i - 1] - 1;
    ans *= calc(len);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
