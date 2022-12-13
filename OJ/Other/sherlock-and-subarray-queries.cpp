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

template <typename T, T (*ut)(), T (*f)(T, T)>
struct SegTree {
 private:
  int n, _log;
  vector<T> val;
  void _update(int t) { val[t] = f(val[t << 1 | 0], val[t << 1 | 1]); }

 public:
  SegTree() = default;
  SegTree(const vector<T> &v) {
    n = 1, _log = 0;
    while (n < (int)v.size()) n <<= 1, _log++;
    val.resize(n << 1, ut());
    for (int i = 0; i < (int)v.size(); i++) val[i + n] = v[i];
    for (int i = n - 1; i > 0; i--) _update(i);
  }
  ~SegTree() = default;

  void set(int p, const T &dif) {
    val[p += n] = dif;
    for (int i = 1; i <= _log; i++) _update(p >> i);
  }
  T get(int p) { return val[p + n]; }
  T query(int l, int r) {
    if (l == r) return ut();
    T L = ut(), R = ut();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) L = f(L, val[l++]);
      if (r & 1) R = f(val[--r], R);
    }
    return f(L, R);
  }
};

namespace SegTreeUtil {  // Utilization
template <typename T>
T Merge(T a, T b) {
  if (a.first > b.first) {
    return a;
  } else if (a.first == b.first) {
    return {a.first, a.second + b.second};
  } else {
    return b;
  }
}
template <typename T>
T Init() {
  return T(0, 0);
}
template <typename T>
struct Tree : SegTree<T, Init<T>, Merge<T>> {
  using base = SegTree<T, Init<T>, Merge<T>>;
  Tree(const vector<T> &v) : base(v) {}
};
}  // namespace SegTreeUtil
using SegTreeUtil::Tree;

void solve() {
  int n, q; cin >> n >> q;
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].first;
    a[i].second = 1;
  }
  Tree<pair<int, int>> seg(a);
  for (int l, r; q--;) {
    cin >> l >> r;
    const pair<int, int> &ans = seg.query(l - 1, r);
    cout << ans.second << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
