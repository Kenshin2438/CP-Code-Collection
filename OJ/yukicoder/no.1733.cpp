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

template <typename T, typename E, T (*ut)(), E (*ue)(), T (*f)(T, T),
          T (*g)(T, E), E (*h)(E, E)>
struct LazySegTree {
 private:
  int n, _log;
  vector<T> val;
  vector<E> laz;
  void _push(int t) {
    if (laz[t] == ue()) return;
    val[t << 1 | 0] = g(val[t << 1 | 0], laz[t]);
    val[t << 1 | 1] = g(val[t << 1 | 1], laz[t]);
    if ((t << 1) < n) {
      laz[t << 1 | 0] = h(laz[t << 1 | 0], laz[t]);
      laz[t << 1 | 1] = h(laz[t << 1 | 1], laz[t]);
    }
    return laz[t] = ue(), void();
  }
  void _update(int t) { val[t] = f(val[t << 1 | 0], val[t << 1 | 1]); }
  void _apply(int t, const E &dif) {
    if (dif == ue()) return;
    val[t] = g(val[t], dif);
    if (t < n) laz[t] = h(laz[t], dif);
  }

 public:
  LazySegTree() = default;
  LazySegTree(const vector<T> &v) {
    n = 1, _log = 0;
    while (n < (int)v.size()) n <<= 1, _log++;
    T ti = ut();
    E ei = ue();
    val.resize(n << 1, ti), laz.resize(n, ei);
    for (int i = 0; i < (int)v.size(); i++) val[i + n] = v[i];
    for (int i = n - 1; i > 0; i--) _update(i);
  }
  ~LazySegTree() = default;

  void update(int l, int r, const E &dif) {
    if (l == r) return;  // update [l, r)
    l += n, r += n;
    for (int i = _log; i >= 1; i--) {
      if (((l >> i) << i) != l) _push(l >> i);
      if (((r >> i) << i) != r) _push((r - 1) >> i);
    }
    for (int a = l, b = r; a < b; a >>= 1, b >>= 1) {
      if (a & 1) _apply(a++, dif);
      if (b & 1) _apply(--b, dif);
    }
    for (int i = 1; i <= _log; i++) {
      if (((l >> i) << i) != l) _update(l >> i);
      if (((r >> i) << i) != r) _update((r - 1) >> i);
    }
  }
  void set(int p, const T &dif) {
    p += n;
    for (int i = _log; i >= 1; i--) _push(p >> i);
    val[p] = dif;
    for (int i = 1; i <= _log; i++) _update(p >> i);
  }
  T get(int p) {
    p += n;
    for (int i = _log; i >= 1; i--) _push(p >> i);
    return val[p];
  }
  T query(int l, int r) {
    if (l == r) return ut();
    l += n, r += n;
    for (int i = _log; i >= 1; i--) {
      if (((l >> i) << i) != l) _push(l >> i);
      if (((r >> i) << i) != r) _push((r - 1) >> i);
    }
    T L = ut(), R = ut();
    for (int a = l, b = r; a < b; a >>= 1, b >>= 1) {
      if (a & 1) L = f(L, val[a++]);
      if (b & 1) R = f(val[--b], R);
    }
    return f(L, R);
  }
};

namespace SegTreeUtil {  // Utilization
template <typename T>
T Merge_T(T a, T b) {
  return a + b;
}
template <typename T, typename E>
T Modify(T a, E b) {
  return a * b;
}
template <typename E>
E Merge_E(E a, E b) {
  return a * b;
}
template <typename T>
T Init_T() {
  return 0;
}
template <typename E>
E Init_E() {
  return 1;
}
template <typename T, typename E>
struct Tree : LazySegTree<T, E, Init_T<T>, Init_E<E>, Merge_T<T>, Modify<T, E>,
                          Merge_E<E>> {
  using base = LazySegTree<T, E, Init_T<T>, Init_E<E>, Merge_T<T>, Modify<T, E>,
                           Merge_E<E>>;

  Tree() = default;
  Tree(const vector<T> &v) : base(v) {}
  ~Tree() = default;
};
}  // namespace SegTreeUtil
using SegTreeUtil::Tree;

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  vector<int> p(n); iota(all(p), 0);
  sort(all(p), [&](const int &pa, const int &pb) {
    return a[pa] < a[pb];
  });

  vector<mint> _(n + 1, 1);
  Tree<mint, mint> L(_), R(_);
  mint ans = 0;
  for (int i = 0; i < n; i++) {
    mint l = L.query(0, p[i] + 1) / L.get(p[i] + 1);
    mint r = R.query(p[i] + 1, n + 1) / R.get(p[i]);
    ans += l * r * a[ p[i] ];
    L.update(0, p[i] + 1, 2), R.update(p[i] + 1, n + 1, 2);
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
