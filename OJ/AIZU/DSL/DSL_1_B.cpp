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

struct DSU {
  vec<int> p, w;
  DSU(int _) : p(_ + 1), w(_ + 1) { iota(all(p), 0); }
  int f(int _) {
    if (_ == p[_]) return _;
    int res = f(p[_]);
    w[_] += w[p[_]], p[_] = res;
    return res;
  }
  bool same(int u, int v) { return f(u) == f(v); }
  void unite(int u, int v, int z = 0) {
    if (same(u, v)) return assert(w[u] - w[v] == z), void();
    w[p[u]] = z - w[u] + w[v], p[p[u]] = p[v];
  }
};

void SingleTest(int TestCase) {
  int n, q; cin >> n >> q;
  DSU s(n);
  for (int op, x, y, z; q--; ) {
    cin >> op;
    if (op) {
      cin >> x >> y;
      if (s.same(x, y)) cout << s.w[x] - s.w[y] << '\n';
      else cout << "?\n";
    } else {
      cin >> x >> y >> z;
      s.unite(x, y, z);
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
