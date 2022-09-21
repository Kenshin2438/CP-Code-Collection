#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 107;
const int inf = 0x3f3f3f3f;

int n, m, s, t;

struct edge {
  int from, to, rev; ll c;
  edge(int _from, int _to, int _rev, ll _c) {
    from = _from, to = _to, rev = _rev, c = _c;
  }
};
vector<edge> G[maxn];
queue<int> Q;
int d[maxn];

inline void ins(int u, int v, ll c) {
  G[u].emplace_back(u, v, 0, c);
  G[v].emplace_back(v, u, 0, 0);
  G[u].back().rev = int(G[v].size()) - 1;
  G[v].back().rev = int(G[u].size()) - 1;
}

inline bool bfs() {
  memset(d, inf, sizeof(d));
  Q.push(s);
  d[s] = 0;
  while (!Q.empty()) {
    int v = Q.front();
    Q.pop();
    for (edge& e : G[v]) {
      if (e.c > 0 && d[e.to] > d[v] + 1) {
        d[e.to] = d[v] + 1;
        Q.push(e.to);
      }
    }
  }
  return d[t] != inf;
}

inline ll dfs(int v, ll flow) {
  if (v == t || flow == 0) return flow;
  ll res = 0, cur = 0;
  for (edge& e : G[v]) {
    if (e.c > 0 && d[e.to] == d[v] + 1) {
      if ((cur = dfs(e.to, min(flow, e.c))) > 0) {
        res += cur;
        flow -= cur;
        e.c -= cur;
        G[e.to][e.rev].c += cur;
      }
    }
  }
  if (res == 0) d[v] = -1;
  return res;
}

ll Dinic() {
  ll res = 0, cur = 0;
  while (bfs()) {
    while ((cur = dfs(s, inf)) > 0) res += cur;
  }
  return res;
}

int main() {
  scanf("%d %d %d %d", &n, &m, &s, &t);
  int u, v; ll c;
  while (m--) {
    scanf("%d %d %lld", &u, &v, &c);
    ins(u, v, c);
  }
  printf("%lld", Dinic());
  return 0;
}