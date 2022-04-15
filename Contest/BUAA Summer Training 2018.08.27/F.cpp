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

const int N = (int) 1e5 + 10;

int n, m, ans[N];

struct Graph {
  struct node { int to, nex, id; ll w; } E[N << 1];
  int h[N], idx;
  int n, rt;
  ll dis[N];
  vec<int> p[N];
  Graph(int _n, int _rt) : n(_n), rt(_rt) {
    for (int i = 1; i <= n; i++) {
      h[i] = 0, dis[i] = 1e18, p[i].clear();
    }
    idx = 0, dis[rt] = 0;
  }
  void add(int u, int v, int id, int w) {
    ++idx;
    E[idx].to = v;
    E[idx].nex = h[u];
    E[idx].w = w;
    E[idx].id = id;
    h[u] = idx;
  }
  void spfa() {
    vec<bool> inQ(n + 1, false);
    queue<int> Q; Q.push(rt), inQ[rt] = true;
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop(), inQ[u] = false;
      for (int i = h[u]; i; i = E[i].nex) {
        int v = E[i].to; ll w = E[i].w;
        if (dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          p[v].clear(), p[v].push_back(i);
          if (!inQ[v]) Q.push(v), inQ[v] = true;
        } else if (dis[v] == dis[u] + w) {
          p[v].push_back(i);
        }
      }
    }
  }
};

struct edge {
  int u, v; ll w;
} EE[N];



void SingleTest(int TestCase) {
  cin >> n >> m;
  Graph G(n, 1), rG(n, 2);
  for (int i = 1; i <= m; i++) {
    ans[i] = 11;

    int a, b, c; cin >> a >> b >> c;
    G.add(a, b, i, c);
    rG.add(b, a, i, c);
    EE[i].u = a, EE[i].v = b, EE[i].w = c;
  }
  G.spfa(), rG.spfa();
  ll D = G.dis[2];
  assert(G.dis[2] == rG.dis[1]);

  queue<int> Q;


  for (int i = 1; i <= n; i++) {
    if (ans[i] == 11) {
      if (G.dis[EE[i].v] + rG.dis[EE[i].u] + EE[i].w < D) {
        ans[i] = 1;
      } else {
        ans[i] = 0;
      }
    }
  }

  for (int i = 1; i <= m; i++) {
    str res = "";
    if (ans[i] ==  1) res = "HAPPY";
    if (ans[i] ==  0) res = "SOSO";
    if (ans[i] == -1) res = "SAD";
    cout << res << '\n';
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
