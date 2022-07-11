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

void SingleTest(__attribute__((unused)) int TestCase) {
  int n; cin >> n;
  vec<vec<PII>> G(n);
  for (int u, v, x, _ = 1; _ < n; _++) {
    cin >> u >> v >> x;
    --u, --v;
    G[u].emplace_back(v, x);
    G[v].emplace_back(u, x);
  }

  vec<int> dep(n);
  auto dfs = [&](auto &&self, int u, int fa) -> void {
    dep[u] = dep[fa] + 1;
    for (const auto &[v, x] : G[u]) {
      if (v == fa) continue;
      self(self, v, u);
    }
  };
  dfs(dfs, );
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
