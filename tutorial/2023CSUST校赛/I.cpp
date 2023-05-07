#include <bits/stdc++.h>
using namespace std;

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

constexpr int mod = 998244353;
using mint = m32<mod>;

constexpr int N = (int) 1E5 + 10;

int n, q, a[N];
mint b[N];

mint c[N << 2], tc[N << 2], laz[N << 2], tlaz[N << 2];
int pos[N << 2];

#define ld (nd << 1 | 0)
#define rd (nd << 1 | 1)
#define interval int s, int t, int nd

void merge_c(int nd) {
   c[nd] =  c[ld] +  c[rd];
  tc[nd] = tc[ld] + tc[rd];
}

void merge_p(int nd) {
  if (pos[ld] == pos[rd]) {
    pos[nd] = pos[ld];
    pos[ld] = pos[rd] = 0;
  } else {
    pos[nd] = 0;
  }
}

void build(interval) {
  c[nd] = tc[nd] = laz[nd] = tlaz[nd] = 0;
  if (s == t) {
    pos[nd] = a[s];
  } else {
    int m = (s + t) >> 1;
    build(s, m, ld), build(m + 1, t, rd), merge_p(nd);
  }
}

void pushlz_c(interval, pair<mint, mint> val) {
  c[nd] += val.first * (t - s + 1);
  laz[nd] += val.first;

  tc[nd] += val.second * (t - s + 1);
  tlaz[nd] += val.second;
}

void downlz_c(interval) {
  if (laz[nd] == 0 && tlaz[nd] == 0) return;
  auto tag = make_pair(laz[nd], tlaz[nd]);
  int m = (s + t) >> 1;
  pushlz_c(s, m, ld, tag);
  pushlz_c(m + 1, t, rd, tag);
  laz[nd] = tlaz[nd] = 0;
}

void rangeAdd(interval, int L, int R, pair<mint, mint> val) {
  if (L <= s && t <= R) return pushlz_c(s, t, nd, val);
  downlz_c(s, t, nd);
  int m = (s + t) >> 1;
  if (L <= m) rangeAdd(s, m, ld, L, R, val);
  if (R > m) rangeAdd(m + 1, t, rd, L, R, val);
  merge_c(nd);
}

void downlz_p(interval) {
  if (pos[nd] == 0) return;
  pos[ld] = pos[nd];
  pos[rd] = pos[nd];
  pos[nd] = 0;
}

void pushlz_p(interval, pair<int, int> val) {
  mint S = c[nd] * val.second - tc[nd];
  b[pos[nd]] += S;
  pos[nd] = val.first;
  b[pos[nd]] -= S;
}

void rangeAssign(interval, int L, int R, pair<int, int> val) {
  if (L <= s && t <= R && pos[nd] != 0) {
    return pushlz_p(s, t, nd, val);
  }
  downlz_c(s, t, nd);
  downlz_p(s, t, nd);
  int m = (s + t) >> 1;
  if (L <= m) rangeAssign(s, m, ld, L, R, val);
  if (R > m) rangeAssign(m + 1, t, rd, L, R, val);
  merge_c(nd);
  merge_p(nd);
}

void solve() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> a[i];
  build(1, n, 1);
  for (int t = 0; t < q; t++) {
    int op, l, r, w; cin >> op >> l >> r >> w;
    if (op == 1) {
      rangeAssign(1, n, 1, l, r, make_pair(w, t));
    } else {
      rangeAdd(1, n, 1, l, r, make_pair(mint(w), mint(w) * t));
    }
  }
  rangeAssign(1, n, 1, 1, n, make_pair(0, q));
  for (int i = 1; i <= n; i++) {
    cout << b[i] << " \n"[i == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}