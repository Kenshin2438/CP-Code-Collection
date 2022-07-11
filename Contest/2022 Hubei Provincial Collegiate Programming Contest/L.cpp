#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define PLL pair<ll, ll>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

template<typename T, typename E, T (*ut)(), E (*ue)(),
  T (*f)(T, T), T (*g)(T, E), E (*h)(E, E)>
struct LazySegTree {
 private:
  int n, _log;
  vec<T> val;
  vec<E> laz;
  void _push(int t) {
    if (laz[t] == ue()) return ;
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
    if (dif == ue()) return ;
    val[t] = g(val[t], dif);
    if (t < n) laz[t] = h(laz[t], dif);
  }
 public:
  LazySegTree(const vec<T> &v) {
    n = 1, _log = 0;
    while (n < sz(v)) n <<= 1, _log++;
    T ti = ut(); E ei = ue();
    val.resize(n << 1, ti), laz.resize(n, ei);
    for (int i = 0; i < sz(v); i++) val[i + n] = v[i];
    for (int i = n - 1; i > 0; i--) _update(i);
  }
  void update(int l, int r, const E &dif) {
    if (l == r) return ; // update [l, r)
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
  void set(int p) {
    p += n;
    for (int i = _log; i >= 1; i--) _push(p >> i);
    val[p].se ^= 1;
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
      if (b & 1) R = f(R, val[--b]);
    }
    return f(L, R);
  }
};

namespace SegTreeUtil { // Utilization
template <typename T> T Merge_T(T a, T b) {
  return {a.fi + b.fi, a.se + b.se};
}
template <typename T, typename E> T Modify(T a, E b) {
  return {a.fi + b * a.se, a.se};
}
template <typename E> E Merge_E(E a, E b) {
  return a + b;
}
template <typename T> T Init_T() {
  return {0, 0};
}
template <typename E> E Init_E() {
  return 0;
}
template <typename T, typename E> struct Tree
  : LazySegTree<T, E, Init_T<T>, Init_E<E>,
  Merge_T<T>, Modify<T, E>, Merge_E<E>> {
  using base =
    LazySegTree<T, E, Init_T<T>, Init_E<E>,
  Merge_T<T>, Modify<T, E>, Merge_E<E>>;

  Tree(const vec<T> &v) : base(v) {}
};
} using SegTreeUtil::Tree;

void SingleTest(__attribute__((unused)) int TestCase) {
  int n, q; cin >> n >> q;

  vec<PLL> v(n);
  for (auto &&[x, y] : v) cin >> x;
  for (auto &&[x, y] : v) cin >> y;

  Tree<PLL, ll> seg(v);
  for (int op; q--; ) {
    cin >> op;
    
    if (op == 1) {
      int x; cin >> x;
      seg.set(x - 1);
    } else if (op == 2) {
      int x; cin >> x;
      seg.set(x - 1);
    } else if (op == 3) {
      int l, r; cin >> l >> r;
      ll x; cin >> x;
      seg.update(l - 1, r, x);
    } else {
      int l, r; cin >> l >> r;
      auto [ans, _] = seg.query(l - 1, r);
      cout << ans << '\n';
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