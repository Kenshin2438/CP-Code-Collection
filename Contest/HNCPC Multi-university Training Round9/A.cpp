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

void SingleTest(int TestCase) {
  int n; cin >> n;
  vec<vec<int>> tree(n + 1);
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  vec<PII> ans(n + 1);
  int curY = n, curX = 1;
  const function<void(int, int)> sol = [&](int u, int fa) {
    ans[u].se = curY--;
    for (int v : tree[u]) {
      if (v == fa) continue;
      sol(v, u);
    }
    ans[u].fi = curX++;
  };
  sol(1, 0);
  for (int i = 1; i <= n; i++) {
    cout << ans[i].fi << ' ' << ans[i].se << '\n';
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
