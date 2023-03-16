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
  a[4] += b[4] + a[3] * b[0];
  a[3] += b[3];
  a[2] += b[2] + a[0] * b[4] + a[1] * b[0];
  a[1] += b[1] + a[0] * b[3];
  a[0] += b[0];
  return a;
}
template <typename T>
T Init() {
  return T{};
}
template <typename T>
struct Tree : SegTree<T, Init<T>, Merge<T>> {
  using base = SegTree<T, Init<T>, Merge<T>>;
  Tree(const vector<T> &v) : base(v) {}
};
}  // namespace SegTreeUtil
using SegTreeUtil::Tree;

void solve() {
  string s; cin >> s;
  assert(all_of(all(s), [&](const char &c) { return 'a' <= c && c <= 'z'; }));
  int n = sz(s);
  assert(3 <= n && n <= (int) 2e5);
  int q; cin >> q;
  assert(1 <= q && q <= (int) 2e5);
  
  vector<array<ll, 5>> init(n, array<ll, 5>{});
  for (int i = 0; i < n; i++) {
    init[i][0] = s[i] == 'l';
    init[i][3] = s[i] == 'z';
  }
  Tree<array<ll, 5>> seg(init);

  for (int _ = 0; _ < q; _++) {
    string op; cin >> op;
    assert(op == "change" || op == "count-lzl");
    if (op == "count-lzl") {
      int l, r; cin >> l >> r;
      assert(1 <= l && l <= r && r <= n);
      cout << seg.query(l - 1, r)[2] << "\n";
    } else {
      int p; cin >> p;
      assert(1 <= p && p <= n);
      char c; cin >> c;
      assert('a' <= c && c <= 'z');
      seg.set(p - 1, array<ll, 5>{c == 'l', 0, 0, c == 'z', 0});
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}