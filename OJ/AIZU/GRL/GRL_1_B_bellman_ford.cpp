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
#define all(a) a.begin(), a.end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

const int inf = 0x3f3f3f3f;
struct edge {
  int to, weight;
  edge(int to, int _ = inf) : to(to), weight(_) {}
};
int n, m;
vec<vec<edge>> G;
vec<int> dis;

bool bellman_ford(int s) {
  dis.assign(n, inf), dis[s] = 0;
  bool update;
  for (int _ = 0; _ < n; _++) {
    update = false;
    for (int u = 0; u < n; u++) {
      if (dis[u] == inf) continue;
      for (auto [v, d] : G[u]) {
        if (dis[v] > dis[u] + d) {
          dis[v] = dis[u] + d;
          update = true;
        }
      }
    }
    if (!update) break;
  }
  return update;
}

void SingleTest(int TestCase) {
  cin >> n >> m;
  G.resize(n);
  int s; cin >> s;
  for (int u, v, d; m--; ) {
    cin >> u >> v >> d;
    G[u].emplace_back(v, d);
  }
  if (bellman_ford(s)) {
    return cout << "NEGATIVE CYCLE\n", void();
  }
  for (int d : dis) {
    if (d == inf) cout << "INF\n";
    else cout << d << '\n';
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
