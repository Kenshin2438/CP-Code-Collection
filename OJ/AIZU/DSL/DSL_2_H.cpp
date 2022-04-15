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

template<typename T, typename E, T ut, E ue,
  T (*f)(T, T), T (*g)(T, E), E (*h)(E, E)>
struct LazySegTree {
  int n, _log;
  vec<T> val;
  vec<E> laz;
  LazySegTree(const vec<T> &v) {
    n = 1, _log = 0;
    while (n < (int) v.size()) n <<= 1, _log++;
    val.resize(n << 1, ut), laz.resize(n, ue);
    for (int i = 0; i < (int) v.size(); i++) val[i + n] = v[i];
    for (int i = n - 1; i > 0; i--) _update(i);
  }
  void update(int l, int r, const E& dif) {
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
    if (l == r) return ut;
    l += n, r += n;
    for (int i = _log; i >= 1; i--) {
      if (((l >> i) << i) != l) _push(l >> i);
      if (((r >> i) << i) != r) _push((r - 1) >> i);
    }
    T L = ut, R = ut;
    for (int a = l, b = r; a < b; a >>= 1, b >>= 1) {
      if (a & 1) L = f(L, val[a++]);
      if (b & 1) R = f(R, val[--b]);
    }
    return f(L, R);
  }
private:
  void _push(int t) {
    if (laz[t] == ue) return ;
    val[t << 1 | 0] = g(val[t << 1 | 0], laz[t]);
    val[t << 1 | 1] = g(val[t << 1 | 1], laz[t]);
    if ((t << 1) < n) {
      laz[t << 1 | 0] = h(laz[t << 1 | 0], laz[t]);
      laz[t << 1 | 1] = h(laz[t << 1 | 1], laz[t]);
    }
    return laz[t] = ue, void();
  }
  void _update(int t) { val[t] = f(val[t << 1 | 0], val[t << 1 | 1]); }
  void _apply(int t, const E& dif) {
    if (dif == ue) return ;
    val[t] = g(val[t], dif);
    if (t < n) laz[t] = h(laz[t], dif);
  }
};

template<typename T> T Min(T a, T b) { return min<T>(a, b); }
template<typename T> T Add(T a, T b) { return a + b; }

void SingleTest(int TestCase) {
  const ll INF = (ll) 1e18;
  int n; cin >> n;
  int q; cin >> q;
  LazySegTree<ll, ll, INF, 0LL, Min<ll>, Add<ll>, Add<ll>> seg(vec<ll>(n, 0));
  for (int op; q--; ) {
    cin >> op;
    if (op == 0) {
      int s, t; ll x;
      cin >> s >> t >> x;
      seg.update(s, t + 1, x);
    } else {
      int s, t; cin >> s >> t;
      cout << seg.query(s, t + 1) << '\n';
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
