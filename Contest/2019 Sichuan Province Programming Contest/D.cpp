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
  cout << "Case " << TestCase << ": ";
  int n; cin >> n;
  vec<int> lab(n);
  for (int &x : lab) cin >> x, --x;
  vec<vec<int>> G(n);
  for (int u, v, _ = 1; _ < n; _++) {
    cin >> u >> v; --u, --v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  vec<int> lg(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
  }
  vec<PII> app(n, {-1, -1});
  vec<int> dep(n);
  vec<vec<int>> p(n, vec<int>(22, 0));
  auto dfs = [&](auto &&f, int u, int fa) -> void {
    dep[u] = dep[fa] + 1, p[u][0] = fa;
    for (int i = 1; i <= lg[dep[u]]; i++) {
      p[u][i] = p[p[u][i - 1]][i - 1];
    }

    if (app[lab[u]].fi == -1) {
      app[lab[u]].fi = app[lab[u]].se = u;
    } else {
      app[lab[u]].se = u;
    }
    for (int &v : G[u]) {
      if (v == fa) continue;
      f(f, v, u);
    }
  };
  dfs(dfs, 0, 0);
  auto lca = [&](int u, int v) -> int {
    if (dep[u] < dep[v]) swap(u, v);
    while (dep[u] > dep[v]) u = p[u][lg[dep[u] - dep[v]] - 1];
    if (u == v) return u;
    for (int i = lg[dep[u]] - 1; i >= 0; i--) {
      if (p[u][i] != p[v][i]) u = p[u][i], v = p[v][i];
    }
    return p[u][0];
  };
  vec<tuple<int, int, int>> B;
  for (int i = 0; i < n; i++) {
    if (app[i].fi == -1) continue;
    int LCA = lca();
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
