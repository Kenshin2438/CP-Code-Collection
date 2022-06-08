#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <functional>
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
#define all(a) a.begin(), a.end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

template<typename T, typename E, T (*ut)(), E (*ue)(),
  T (*f)(T, T), T (*g)(T, E), E (*h)(E, E)>
struct LazySegTree {
  int n, _log;
  vec<T> val;
  vec<E> laz;
  LazySegTree(const vec<T> &v) {
    n = 1, _log = 0;
    while (n < (int) v.size()) n <<= 1, _log++;
    T ti = ut(); E ei = ue();
    val.resize(n << 1, ti), laz.resize(n, ei);
    for (int i = 0; i < (int) v.size(); i++) val[i + n] = v[i];
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
  void set(int p, const T& dif) {
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
      if (b & 1) R = f(R, val[--b]);
    }
    return f(L, R);
  }
private:
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
};

namespace SegTreeUtil { // Utilization
template <typename T> T Merge_T(T a, T b) {
  if (b.se == 0 || a.fi < b.fi) return a;
  if (a.se == 0 || b.fi < a.fi) return b;
  return a.se += b.se, a;
}
template <typename T, typename E> T Modify(T a, E b) {
  return a.fi += b, a;
}
template <typename E> E Merge_E(E a, E b) {
  return a + b;
}
template <typename T> T Init_T() {
  return T{0, 0};
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

int n;
vec<int> xs, ys, xt, yt;

ll Perimeter() {
  vec<int> Y(n << 1);
  vec<array<int, 4>> line(n << 1);
  for (int i = 0; i < n; i++) {
    Y[i << 1 | 0] = ys[i], Y[i << 1 | 1] = yt[i];
    line[i << 1 | 0] = {xs[i], ys[i], yt[i],  1};
    line[i << 1 | 1] = {xt[i], ys[i], yt[i], -1};
  }
  const int R = 1000000 + 10, L = -R;
  Y.push_back(L), Y.push_back(R);
  sort(all(Y)), Y.erase(unique(all(Y)), Y.end());
  sort(all(line), [&](array<int, 4> a, array<int, 4> b) {
    return (a[0] == b[0]) ? (a[3] > b[3]) : (a[0] < b[0]);
  });
  vec<PII> s(SZ(Y) - 1);
  for (int i = 0; i < SZ(Y) - 1; i++) {
    s[i].fi = 0, s[i].se = Y[i + 1] - Y[i];
  }
  Tree<PII, int> tr(s); // Min cnt && Min
  ll ans = 0, pre = 0;
  for (int i = 0; i < SZ(line); i++) {
    PII Q = tr.query(0, SZ(s));
    ll len = R - L - (Q.fi == 0) * Q.se;
    ans += abs(len - pre);
    int pl = lower_bound(all(Y), line[i][1]) - Y.begin();
    int pr = lower_bound(all(Y), line[i][2]) - Y.begin();
    tr.update(pl, pr, line[i][3]), pre = len;
  }
  return ans + abs(pre);
}

void SingleTest(int TestCase) {
  cin >> n;
  xs.resize(n);
  ys.resize(n);
  xt.resize(n);
  yt.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> xs[i] >> ys[i];
    cin >> xt[i] >> yt[i];
  }
  ll ans = 0;
  ans += Perimeter();
  swap(xs, ys), swap(xt, yt);
  ans += Perimeter();
  cout << ans << '\n';
}

void init() {}

int main() {
  // cin.tie(nullptr)->sync_with_stdio(false);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
