#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

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
  friend ostream &operator<<(ostream &os, const m32<mod> &m) {
    return os << m.v;
  }
};

template <int mod> struct CRT {
  using mint = m32<mod>;

  template <typename T> pair<T, T> exgcd(T a, T b) {
    bool nega = (a < 0), negb = (b < 0);
    T x = 1, y = 0, r = 0, s = 1;
    while (b) {
      T t = a / b;
      r ^= x ^= r ^= x -= t * r;
      s ^= y ^= s ^= y -= t * s;
      b ^= a ^= b ^= a %= b;
    }
    return {nega ? -x : x, negb ? -y : y};
  }
  template <typename T> T inv(T a, T m) {
    auto res = exgcd<T>(a, m).first % m;
    return res < 0 ? res + mod : res;
  }

  mint merge(const vector<int> &R, const vector<int> &M) {
    mint res = 0;
    for (int i = 0; i < static_cast<int>(M.size()); i++) {
      res += mint(R[i]) * (mod / M[i]) * inv(mod / M[i], M[i]);
    }
    return res;
  }
};

template <int P> struct Combinations {
  using Mint = m32<P>;
  using i64 = int64_t;
  Mint C[P][P];
  Mint S[P][P];
  Mint B[P];
  Combinations() {
    for (int n = 0; n < P; ++n) {
      C[n][0] = C[n][n] = 1;
      for (int k = 1; k < n; ++k) {
        C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
      }
    }
    for (int n = 0; n < P; ++n) {
      S[n][0] = 0;
      S[n][n] = 1;
      for (int k = 1; k < n; ++k) {
        S[n][k] = S[n - 1][k - 1] + S[n - 1][k] * k;
      }
    }
    for (int n = 0; n < P; ++n) {
      B[n] = 0;
      for (int k = 0; k <= n; ++k) {
        B[n] += S[n][k];
      }
    }
  }
  Mint getC(i64 n, i64 k) const {
    Mint ret = 1;
    for (; n; n /= P, k /= P) {
      ret *= C[n % P][k % P];
    }
    return ret;
  }
  Mint getS(i64 n, i64 k) const {
    const i64 y = k / P;
    const i64 dk = k % P;
    const i64 x = (n - (y + (dk ? 1 : 0))) / (P - 1);
    const i64 dn = n - ((P - 1) * x + y);
    return getC(x, y) * S[dn][dk];
  }
  Mint getB(i64 n) const {
    auto mul = [&](const vector<Mint> &fs, const vector<Mint> &gs) {
      vector<Mint> hs(P + P - 1, 0);
      for (int i = 0; i < P; ++i) for (int j = 0; j < P; ++j) {
        hs[i + j] += fs[i] * gs[j];
      }
      for (int i = P + P - 1; --i >= P; ) {
        hs[i - (P - 1)] += hs[i];
        hs[i - P] += hs[i];
      }
      hs.resize(P);
      return hs;
    };
    vector<Mint> xs(P, 0), ys(P, 0);
    xs[1] = 1;
    ys[0] = 1;
    for (i64 e = n; e > 0; e >>= 1, xs = mul(xs, xs)) {
      if (e & 1) ys = mul(ys, xs);
    }
    Mint ret = 0;
    for (int i = 0; i < P; ++i) {
      ret += ys[i] * B[i];
    }
    return ret;
  }
};

const vector<int> M = { 31, 37, 41, 43, 47 };

Combinations<31> C31;
Combinations<37> C37;
Combinations<41> C41;
Combinations<43> C43;
Combinations<47> C47;

void solve() {
  int n; cin >> n;
  vector<int> R = {
    static_cast<int>(C31.getB(n).v),
    static_cast<int>(C37.getB(n).v),
    static_cast<int>(C41.getB(n).v),
    static_cast<int>(C43.getB(n).v),
    static_cast<int>(C47.getB(n).v)
  };
  cout << CRT<95041567>().merge(R, M) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
