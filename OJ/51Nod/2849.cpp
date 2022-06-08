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

struct Weighted_DSU {
  vec<int> p, val;

  Weighted_DSU() {}
  Weighted_DSU(int n, int init = 0) : p(n), val(n, init) {
    iota(all(p), 0);
  }

  int find(int x) {
    if (x == p[x]) return x;
    int fa = find(p[x]);
    val[x] += val[p[x]];
    return p[x] = fa;
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
  int weight(int x) {
    return find(x), val[x];
  }
  int diff(int x, int y) {
    return weight(y) - weight(x);
  }
  bool unite(int x, int y, int dif = 0) {
    dif = weight(y) - weight(x) - dif;
    x = find(x), y = find(y);
    if (x == y) return false;
    p[x] = y, val[x] = dif;
    return true;
  }
};

void SingleTest(__attribute__((unused)) int TestCase) {
  int n; cin >> n;
  vec<int> p(n);
  for (int &x : p) cin >> x, --x;

  Weighted_DSU dsu(n);
  int ans = (int) 2e9;
  for (int i = 0; i < n; i++) {
    if (dsu.unite(i, p[i], -1) == false) {
      ans = min(ans, dsu.diff(i, p[i]) + 1);
    }
  }

  cout << ans << '\n';
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