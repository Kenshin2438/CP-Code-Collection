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
  vec<vec<int>> G(n + 1);
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  vec<int> dep(n + 1, 0);
  auto dfs = [&](auto self, int u, int fa) -> void {
    dep[u] = dep[fa] + 1;
    for (int v : G[u]) {
      if (v == fa) continue;
      self(self, v, u);
    }
  };
  dfs(dfs, 1, 0);
  db ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = ans + 1.0 / dep[i];
  }
  cout << ans << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
