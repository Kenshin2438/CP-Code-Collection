#include "../main.hpp"

const int inf = 0x3f3f3f3f;
struct edge {
  int to, weight;
  edge(int to, int _ = inf) : to(to), weight(_) {}
};
int n, m;
vec<vec<edge>> G;
vec<int> dis;

bool spfa(int s) {
  dis.assign(n, inf);
  vec<int> cnt(n, 0);
  vec<bool> inq(n, false);
  queue<int> Q;
  Q.push(s), inq[s] = true, dis[s] = 0;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop(), inq[u] = false;
    for (auto [v, d] : G[u]) {
      if (dis[v] > d + dis[u]) {
        dis[v] = d + dis[u];
        cnt[v] = cnt[v] + 1;
        if (cnt[v] == n) return true;
        if (!inq[v]) Q.push(v), inq[v] = true;
      }
    }
  }
  return false;
}
