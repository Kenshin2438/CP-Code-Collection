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

struct Graph { // Tree-Graph
  int n;
  vec<vec<PII>> G;

  Graph(int _n) : n(_n), G(_n) {
    for (int u, v, w, _ = 1; _ < n; _++) {
      cin >> u >> v >> w;
      G[u].emplace_back(v, w);
      G[v].emplace_back(u, w);
    }
  }

  vec<int> height() {
    vec<int> dis(n, 0);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
      for (const auto &[v, w] : G[u]) {
        if (v == fa) continue;
        self(self, v, u);
        dis[u] = max(dis[u], dis[v] + w);
      }
    };
    dfs(dfs, 0, -1); // 0-indexed
    vec<int> h(n, 0);
    auto sol = [&](auto &&self, int u, int fa, int pre) -> void {
      vec<int> res{ pre };
      for (const auto &[v, w] : G[u]) {
        if (v == fa) continue;
        res.emplace_back(dis[v] + w);
      }
      sort(all(res), greater<int>());
      h[u] = res[0];
      for (const auto &[v, w] : G[u]) {
        if (v == fa) continue;
        if (dis[v] + w == h[u]) {
          self(self, v, u, res[1] + w);
        } else {
          self(self, v, u, res[0] + w);
        }
      }
    };
    sol(sol, 0, -1, 0);
    return h;
  }
};

void SingleTest(int TestCase) {
  int n; cin >> n;
  Graph tree(n);
  auto h = tree.height();
  for (int x : h) cout << x << '\n';
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
