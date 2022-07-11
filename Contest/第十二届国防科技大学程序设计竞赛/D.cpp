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
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

struct DSU {
  vec<int> p;

  DSU() {}
  DSU(int _) : p(_ + 1) { iota(all(p), 0); }

  int f(int _) { return _ == p[_] ? _ : p[_] = f(p[_]); }
  bool same(int u, int v) { return f(u) == f(v); }
  bool unite(int u, int v) {
    u = f(u), v = f(v);
    if (u == v) return false;
    return p[u] = v, true;
  }
};

void SingleTest(__attribute__((unused)) int TestCase) {
  int n, k; cin >> n >> k;

  DSU dsu(n);
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    dsu.unite(x, i);
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += i == dsu.f(i);
  }

  if (ans > k) cout << ans - k << '\n';
  else cout << ((k - ans) % 2 ? 1 : 2) << '\n';
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
