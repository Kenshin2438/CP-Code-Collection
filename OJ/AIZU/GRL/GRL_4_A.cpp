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

struct Graph {
  bool isDAG;
  vec<int> deg;

  int n, m;
  vec<vec<int>> G;

  Graph(int _n, int _m) : n(_n), m(_m), G(_n) {
    deg.assign(n, 0);
    for (int u, v, _ = 0; _ < m; _++) {
      cin >> u >> v;
      G[u].emplace_back(v);
      deg[v] ++;
    }

    int cnt = 0;
    queue<int> Q;
    for (int i = 0; i < n; i++) if (deg[i] == 0) Q.emplace(i);
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      cnt++;
      for (int v : G[u]) {
        if (--deg[v] == 0) Q.emplace(v);
      }
    }
    isDAG = (cnt == n);
  }
};

void SingleTest(int TestCase) {
  int n, m; cin >> n >> m;
  Graph graph(n, m);
  cout << (graph.isDAG ? 0 : 1) << '\n';
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
