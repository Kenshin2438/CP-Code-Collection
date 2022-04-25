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

void Dijkstra(int s) {
  dis.assign(n, inf);
  priority_queue<PII> pq;
  pq.emplace(0, s), dis[s] = 0;
  while (!pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop(), du = -du;
    if (dis[u] < du) continue;
    for (auto [v, d] : G[u]) {
      if (dis[v] > d + du) {
        dis[v] = d + du;
        pq.emplace(-dis[v], v);
      }
    }
  }
}

void SingleTest(int TestCase) {
  cin >> n >> m;
  G.resize(n);
  int s; cin >> s;
  for (int u, v, d; m--; ) {
    cin >> u >> v >> d;
    G[u].emplace_back(v, d);
  }
  Dijkstra(s);
  for (int d : dis) {
    if (d >= inf) cout << "INF\n";
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
