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
  int diameter() {
    // Attention : n = 1
    vec<int> dis(n, 0);
    auto dfs = [&](auto && self, int u, int fa) -> void {
      for (auto [v, d] : G[u]) {
        if (v != fa) {
          dis[v] = dis[u] + d;
          self(self, v, u);
        }
      }
    };
    dfs(dfs, 0, -1); // 0-indexed
    int cur = max_element(all(dis)) - begin(dis);
    dis.assign(n, 0);
    dfs(dfs, cur, -1);
    return *max_element(all(dis));
  }
};

void SingleTest(int TestCase) {
  int n; cin >> n;
  Graph tree(n);
  cout << tree.diameter() << '\n';
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
