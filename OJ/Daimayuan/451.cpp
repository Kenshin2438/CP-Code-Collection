#define PROBLEM "http://oj.daimayuan.top/course/10/problem/451"

#include "bits/stdc++.h"
using namespace std;

#ifdef LOCAL
  #include "debug.hpp"
#else
  #define debug(...)
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(), a.end()

typedef double db;
typedef long long ll;

void SingleTest(int TestCase) {
  int n, q; cin >> n >> q;
  vec<int> val(n + 1, 0), dep(n + 1, 0), lg(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> val[i];
    lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
  }
  vec<vec<int>> G(n + 1, vec<int>());
  for (int i = 2; i <= n; i++) {
    int u, v; cin >> u >> v;
    G[u].pb(v), G[v].pb(u);
  }
  vec<vec<int>> p(n + 1, vec<int>(22, 0));
  vec<int> sum(n + 1, 0);
  auto dfs = [&](auto self, int u, int fa) -> void {
    dep[u] = dep[fa] + 1, p[u][0] = fa;
    sum[u] = sum[fa] ^ val[u];
    for (int i = 1; i <= lg[dep[u]]; i++) {
      p[u][i] = p[p[u][i - 1]][i - 1];
    }
    for (int v : G[u]) {
      if (v != fa) self(self, v, u);
    }
  };
  dfs(dfs, 1, 0);
  auto lca = [&](int u, int v) -> int {
    if (dep[u] < dep[v]) swap(u, v);
    while (dep[u] > dep[v]) u = p[u][lg[dep[u] - dep[v]] - 1];
    if (u == v) return u;
    for (int i = lg[dep[u]] - 1; i >= 0; i--) {
      if (p[u][i] != p[v][i]) u = p[u][i], v = p[v][i];
    }
    return p[u][0];
  };
  while (q--) {
    int u, v; cin >> u >> v;
    cout << (sum[u] ^ sum[v] ^ val[lca(u, v)]) << '\n';
  }
}

void init() { }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--; ) SingleTest(++TestCase);
  return 0;
}
