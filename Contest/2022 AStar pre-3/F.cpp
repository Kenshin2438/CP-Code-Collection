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
  return {
    a[0] + b[0],
    a[1] + b[1],
    a[3]
  };
}
template <typename T, typename E>
T Modify(T a, E b) {
  return {
    a[1] * b,
    a[1],
    b
  };
}
template <typename E>
E Merge_E(E a, E b) {
  return b;
}
template <typename T>
T Init_T() {
  return {0, 0, 1};
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

#define gc() (p1 == p2 ? (p2 = buf + fread(p1 = buf, 1, 1 << 20, stdin), p1 == p2 ? EOF : *p1++) : *p1++)
#define read() ({ long long x = 0, f = 1; char c = gc(); while(c < '0' || c > '9') { if (c == '-') f = -1; c = gc();} while(c >= '0' && c <= '9') x = x * 10 + (c & 15), c = gc(); f * x; })
#define pc(x) (p - puf == 1 << 20 ? (fwrite(puf, 1, 1 << 20, stdout), p = puf) : 0, *p++ = x)
#define print(x, b) ({ pt(x), pc(b); })
char buf[1 << 20], *p1, *p2, puf[1 << 20], *p = puf;
int pt(long long x) {
  return x <= 9 ? pc(x + '0') : (pt(x / 10), pc(x % 10 + '0'));
}

void solve() {
  int n = read();
  int q = read();

  vector<ll> a(n);
  for (ll &x : a) x = read();

  vector<vector<pair<int, int>>> Q(n);
  for (int i = 0; i < q; i++) {
    int l = read() - 1;
    int r = read() - 1;
    Q[l].emplace_back(r, i);
  }

  vector<array<ll, 3>> v(n);
  for (int i = 0; i < n; i++) {
    v[i][0] = v[i][1] = a[i], v[i][2] = 1;
  }
  Tree<array<ll, 3>, ll> seg(v);

  vector<ll> ans(q);
  vector<int> stk;
  for (int i = n - 1; i >= 0; i--) {
    while (!stk.empty() && a[stk.back()] <= a[i]) {
      int l = stk.back();
      stk.pop_back();
      int r = stk.empty() ? n - 1 : stk.back() - 1;
      if (a[l] != a[i]) seg.update(l, r + 1, a[i]);
    }
    stk.push_back(i);
    seg.update(i, i + 1, a[i]);

    for (const auto &P : Q[i]) {
      int r = P.first, id = P.second;
      ans[id] = seg.query(i, r + 1)[0];
    }
  }
  for (const ll &x : ans) print(x, '\n');
}

int main() {
  // cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();
  fwrite(puf, 1, p - puf, stdout);
  return 0;
}
