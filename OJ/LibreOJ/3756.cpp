#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) int(x.size())

int k;
vector<vector<int>> binom;

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

  void set(int p) {
    p += n;

    val[p][2] = binom[++val[p][0]][k] * binom[--val[p][1]][k];
    for (int i = 1; i <= _log; i++) _update(p >> i);
  }
  T get(int p) { return val[p + n]; }
  T query(int l, int r) {
    if (l == r) return ut();
    T L = ut(), R = ut();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) L = f(L, val[l++]);
      if (r & 1) R = f(R, val[--r]);
    }
    return f(L, R);
  }
};

namespace SegTreeUtil {  // Utilization
template <typename T>
T Merge(T a, T b) {
  return { a[0], a[1], a[2] + b[2] };
}
template <typename T>
T Init() {
  return T();
}
template <typename T>
struct Tree : SegTree<T, Init<T>, Merge<T>> {
  using base = SegTree<T, Init<T>, Merge<T>>;
  Tree(const vector<T> &v) : base(v) {}
};
}  // namespace SegTreeUtil
using SegTreeUtil::Tree;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m, w; cin >> n >> m >> w;

  vector<pair<int, int>> p(w);
  vector<int> X, Y;
  for (auto &&[x, y] : p) {
    cin >> x >> y;
    X.emplace_back(x);
    Y.emplace_back(y);
  }
  sort(all(X)), X.erase(unique(all(X)), end(X));
  sort(all(Y)), Y.erase(unique(all(Y)), end(Y));
  for (auto &&[x, y] : p) {
    x = lower_bound(all(X), x) - begin(X);
    y = lower_bound(all(Y), y) - begin(Y);
  }

  cin >> k;
  binom.resize(w + 1, vector<int>(k + 1, 0));
  for (int i = 0; i <= w; i++) {
    binom[i][0] = 1;
    for (int j = 1; j <= i && j <= k; j++) {
      binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]);
    }
  }

  vector<array<int, 3>> col(w, {0, 0, 0});
  vector<vector<int>> R(X.size());
  for (const auto &[x, y] : p) {
    R[x].emplace_back(y);
    col[y][1]++;
  }
  Tree<array<int, 3>> seg(col);

  int ans = 0;
  for (auto &&v : R) {
    if (v.empty()) continue;
    sort(all(v));
    for (int i = 0; i < v.size(); i++) {
      if (i >= k && v.size() - i >= k && v[i] != v[i - 1] + 1) {
        ans += seg.query(v[i - 1] + 1, v[i])[2] * binom[i][k] * binom[v.size() - i][k];
      }
      seg.set(v[i]);
    }
  }
  cout << (ans & 2147483647) << '\n';
  return 0;
}
