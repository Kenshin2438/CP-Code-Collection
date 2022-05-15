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
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

template <typename T, T (*ut)(), T (*f)(T, T)>
struct SegTree {
 private:
  int n, _log;
  vec<T> val;
  void _update(int t) { val[t] = f(val[t << 1 | 0], val[t << 1 | 1]); }

 public:
  SegTree(const vec<T> &v) {
    n = 1, _log = 0;
    while (n < SZ(v)) n <<= 1, _log++;
    val.resize(n << 1, ut());
    for (int i = 0; i < SZ(v); i++) val[i + n] = v[i];
    for (int i = n - 1; i > 0; i--) _update(i);
  }
  void set(int p, const T& dif) {
    val[p += n] = dif;
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
template <typename T> T Merge(T a, T b) { return a + b; }
template <typename T> T Init() { return T(); }
template <typename T>
struct Tree : SegTree<T, Init<T>, Merge<T>> {
  using base = SegTree<T, Init<T>, Merge<T>>;
  Tree(const vec<T> &v) : base(v) {}
};
}  // namespace SegTreeUtil
using SegTreeUtil::Tree;

void SingleTest(int TestCase) {
  int n, q; cin >> n >> q;
  Tree<int> row(vec<int>(n, 0)), col = row;
  vec<int> R(n, 0), C(n, 0);
  for (int op; q--; ) {
    cin >> op;
    if (op == 1) {
      int x, y; cin >> x >> y;
      R[--x]++, C[--y]++;
      row.set(x, R[x] > 0), col.set(y, C[y] > 0);
    } else if (op == 2) {
      int x, y; cin >> x >> y;
      R[--x]--, C[--y]--;
      row.set(x, R[x] > 0), col.set(y, C[y] > 0);
    } else { // query
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      x1--, y1--, x2--, y2--;
      int cntR = row.query(x1, x2 + 1);
      int cntC = col.query(y1, y2 + 1);
      if (cntR == x2 - x1 + 1 || cntC == y2 - y1 + 1) {
        cout << "Yes" << '\n';
      } else {
        cout << "No" << '\n';
      }
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
