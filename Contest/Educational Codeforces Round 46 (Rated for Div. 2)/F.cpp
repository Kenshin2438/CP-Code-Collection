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

const int inf = 0x3f3f3f3f;
namespace SegTreeUtil {  // Utilization
template <typename T>
T Merge(T a, T b) {
  return min(a, b);
}
template <typename T>
T Init() {
  return {inf, inf};
}
template <typename T>
struct Tree : SegTree<T, Init<T>, Merge<T>> {
  using base = SegTree<T, Init<T>, Merge<T>>;
  Tree(const vector<T> &v) : base(v) {}
};
}  // namespace SegTreeUtil
using SegTreeUtil::Tree;

void solve() {
  int n; cin >> n;

  vector<int> a(n);
  for (int &x : a) cin >> x;

  const int N = 5e5 + 10;
  vector<int> p(N, -1), pre(n);
  for (int i = 0; i < n; i++) {
    pre[i] = p[a[i]], p[a[i]] = i;
  }

  vector<pair<int, int>> v(n);
  for (int i = 0; i < n; i++) {
    v[i].first = pre[i], v[i].second = i;
  }
  Tree<pair<int, int>> seg(v);

  int q; cin >> q;
  vector<vector<pair<int, int>>> Q(n);
  for (int l, r, _ = 0; _ < q; _++) {
    cin >> l >> r;
    --l, --r;
    Q[r].emplace_back(l, _);
  }

  vector<int> ans(q);
  for (int i = 0; i < n; i++) {
    if (~pre[i]) seg.set(pre[i], {inf, pre[i]});
    for (const auto &[l, id] : Q[i]) {
      auto [leftmost, pos] = seg.query(l, i + 1);
      if (leftmost < l) ans[id] = a[pos];
    }
  }

  for (const int &x : ans) cout << x << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
