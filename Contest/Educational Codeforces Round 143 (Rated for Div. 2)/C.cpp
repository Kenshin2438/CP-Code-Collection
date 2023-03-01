#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

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
  return a + b;
}
template <typename E>
E Merge_E(E a, E b) {
  return a + b;
}
template <typename T>
T Init_T() {
  return 0;
}
template <typename E>
E Init_E() {
  return 0;
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
  vector<ll> a(n), b(n);
  for (auto &x : a) cin >> x;
  for (auto &x : b) cin >> x;

  if (n == 1) {
    return cout << min(b[0], a[0]) << "\n", void();
  }

  auto sb = b;
  partial_sum(all(sb), begin(sb));
  ll S = sb.back();

  vector<ll> _(n);
  Tree<ll, ll> ft(_);

  vector<ll> ans(n);
  for (int i = 0; i < n; i++) {
    ll PS = (i == 0 ? 0 : sb[i - 1]);
    // if (a[i] <= SS) {
      int pos = lower_bound(all(sb), a[i] + PS) - begin(sb);
      if (pos == n) {
        ft.update(i, n, 1LL);
      } else {
        ft.update(i, pos, 1LL);
        ans[pos] += min(b[pos], a[i] - ((pos == 0 ? 0 : sb[pos - 1]) - PS));
      }
      // debug(i, pos);
    // } else {
    //   ft.update(i, n, 1LL), a[i] -= SS;
    //   ft.update(0, n, a[i] / S), a[i] %= S;
    //   int pos = lower_bound(all(sb), a[i]) - begin(sb);
    //   ft.update(i, pos, 1LL);
    //   // debug(i, pos);
    //   ans[pos] += a[i] - (pos == 0 ? 0 : sb[pos - 1]);
    // }
  }
  for (int i = 0; i < n; i++) {
    ll times = ft.get(i);
    cout << ans[i] + b[i] * times << " \n"[i + 1 == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}