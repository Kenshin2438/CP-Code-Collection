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
  friend ostream &operator<<(ostream &os, const m32<mod> &m) {
    return os << m.v;
  }
};

const int mod = 998244353;
using mint = m32<mod>;

using ull = unsigned long long;

#include <bits/extc++.h>
const int SEED = chrono::steady_clock::now().time_since_epoch().count();
struct chash {  // To use most bits rather than just the lowest ones:
  const ull C = ll(4e18 * acos(0)) | 71;  // large odd number
  int operator()(int x) const { return __builtin_bswap64((x ^ SEED) * C); }
};
using HashMap = __gnu_pbds::gp_hash_table<int, int, chash>;

ull splitmix64(ull x) {
  // http://xorshift.di.unimi.it/splitmix64.c
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}

void solve() {
  int n; cin >> n;

  HashMap Ht;
  vector<mint> dp(n + 1);
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    if (Ht.find(x) != end(Ht)) {
      dp[i] = dp[i - 1] * 2 - dp[Ht[x] - 1];
    } else {
      dp[i] = dp[i - 1] * 2;
    }
    Ht[x] = i;
  }
  cout << dp[n] - 1 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
