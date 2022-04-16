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
#define all(a) a.begin(), a.end()

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

namespace SegTreeUtil {
template<typename T> using P = pair<T, T>;
template<typename T> P<T> Merge(P<T> a, P<T> b) {
  if (b.se == 0 || a.fi < b.fi) return a;
  if (a.se == 0 || b.fi < a.fi) return b;
  return P<T>(a.fi, a.se + b.se);
}
template <typename T> T Zero() { return T(0); }
template <typename T> P<T> P_Zero() { return P<T>(0, 0); }
template <typename T> P<T> P_Add(P<T> a, T b) {
  return P<T>(a.fi + b, a.se);
}
template <typename T> T Add(T a, T b) { return a + b; }
template<typename T> struct MinCntTree
  : LazySegTree<P<T>, T, P_Zero<T>, Zero<T>, Merge<T>, P_Add<T>, Add<T>> {
  using base =
    LazySegTree<P<T>, T, P_Zero<T>, Zero<T>, Merge<T>, P_Add<T>, Add<T>>;
  MinCntTree(const vec<P<T>> &v) : base(v) {}
};
} using SegTreeUtil::MinCntTree;

void SingleTest(int TestCase) {
  int n; cin >> n;
  vec<int> Y(n << 1);
  vec<tuple<int, int, int, int>> line(n << 1);
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1; // top-left
    cin >> x2 >> y2; // bottom-right
    Y[i << 1 | 0] = y1, Y[i << 1 | 1] = y2;
    line[i << 1 | 0] = { x1, y1, y2,  1 };
    line[i << 1 | 1] = { x2, y1, y2, -1 };
  }
  constexpr int ss = 1'000'000'007, tt = -ss;
  Y.emplace_back(ss), Y.emplace_back(tt);
  sort(all(Y)), Y.erase(unique(all(Y)), Y.end()), sort(all(line));
  int _ = (int) Y.size();
  vec<PII> s(_ - 1);
  for (int i = 0; i < _ - 1; i++) s[i] = PII(0, Y[i + 1] - Y[i]);
  MinCntTree<int> tree(s);
  // MinCnt -> total_length - uncovered_length
  ll Area = 0, pre = tt;
  for (auto [x, ys, yt, type] : line) {
    auto [cnt, len] = tree.query(0, _ - 1);
    ll L = ss - tt - (cnt == 0) * len;
    Area += (x - pre) * L;
    int ps = lower_bound(all(Y), ys) - Y.begin();
    int pt = lower_bound(all(Y), yt) - Y.begin();
    pre = x, tree.update(ps, pt, type);
  }
  cout << Area << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout() << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
