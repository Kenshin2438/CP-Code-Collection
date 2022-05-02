#include "../main.hpp"

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
