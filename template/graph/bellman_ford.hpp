#include "../main.hpp"

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
