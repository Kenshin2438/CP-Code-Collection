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
  void _update(int t) {
    val[t] = f(val[t << 1 | 0], val[t << 1 | 1]);
  }
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

namespace SegTreeUtil { // Utilization
template <typename T> T Merge(T a, T b) {
  T res;
  res.l = min(a.l, b.l);
  res.r = max(a.r, b.r);
  if (res.l == a.l) res.pl = a.pl;
  else res.pl = b.pl;
  if (res.r == a.r) res.pr = a.pr;
  else res.pr = b.pr;
  return res;
}
template <typename T> T Init() {
  return T();
}
template <typename T>
struct Tree : SegTree<T, Init<T>, Merge<T>> {
  using base = SegTree<T, Init<T>, Merge<T>>;
  Tree(const vec<T> &v) : base(v) {}
};
} using SegTreeUtil::Tree;

const int inf = numeric_limits<int>::max() / 2;

struct node {
  int l, pl; // 区间能到的最左端
  int r, pr; // 区间能到的最右端
  node() : l(inf), r(-inf) {};
};

void SingleTest(int TestCase) {
  int n, a, b;
  cin >> n >> a >> b;
  a--, b--;
  vec<node> v(n);
  vec<int>  p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    v[i].l = i - p[i], v[i].pl = i;
    v[i].r = i + p[i], v[i].pr = i;
  }
  Tree<node> tr(v);
  vec<int> d(n, inf);
  queue<int> Q;
  Q.push(a), d[a] = 0, tr.set(a, node());
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    int l = max(0, u - p[u]);
    int r = min(n, u + p[u] + 1);
    while (true) {
      node tmp = tr.query(l, u);
      if (tmp.r >= u) {
        int v = tmp.pr;
        Q.push(v);
        tr.set(v, node());
        d[v] = d[u] + 1;
      } else break;
    }
    while (true) {
      node tmp = tr.query(u + 1, r);
      if (tmp.l <= u) {
        int v = tmp.pl;
        Q.push(v);
        tr.set(v, node());
        d[v] = d[u] + 1;
      } else break;
    }
  }
  cout << d[b] << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
