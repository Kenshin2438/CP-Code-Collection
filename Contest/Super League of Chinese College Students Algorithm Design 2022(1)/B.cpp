#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;

const int N = 300, inf = 0x3f3f3f3f;

int n, m, q;
int s, t, dis[N][N], XS[N], XT[N], YS[N], YT[N];

int getPos(int x, int y) { return x * m + y; }

struct DSU {
  vector<int> p;

  DSU() = default;
  DSU(int n) : p(n, -1) {}
  ~DSU() = default;

  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  bool same(int u, int v) { return find(u) == find(v); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;

    p[u] += p[v], p[v] = u;
    return true;
  }
};

void solve() {
  cin >> n >> m >> q;
  {
    int x, y; cin >> x >> y;
    s = getPos(x, y);
  }
  {
    int x, y; cin >> x >> y;
    t = getPos(x, y);
  }
  for (int i = 0; i < q; i++) {
    cin >> XS[i] >> YS[i];
    cin >> XT[i] >> YT[i];
  }

  int N = getPos(n - 1, m - 1), ans = 10000;
  for (int st = 0; st < (1 << q); st++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int cur = getPos(i, j);
        {
          int x = i - 1, y = j;
          if (x >= 0 && x < n && y >= 0 && y < m) {
            int now = getPos(x, y);
            dis[cur][now] = dis[now][cur] = 1;
          }
        }
        {
          int x = i + 1, y = j;
          if (x >= 0 && x < n && y >= 0 && y < m) {
            int now = getPos(x, y);
            dis[cur][now] = dis[now][cur] = 1;
          }
        }
        {
          int x = i, y = j - 1;
          if (x >= 0 && x < n && y >= 0 && y < m) {
            int now = getPos(x, y);
            dis[cur][now] = dis[now][cur] = 1;
          }
        }
        {
          int x = i, y = j + 1;
          if (x >= 0 && x < n && y >= 0 && y < m) {
            int now = getPos(x, y);
            dis[cur][now] = dis[now][cur] = 1;
          }
        }
      }
    }

    for (int o = 0; o < q; o++)
      if (st >> o & 1) {
        int xs = XS[o];
        int xt = XT[o];
        int ys = YS[o];
        int yt = YT[o];

        if (xs == xt && ys == yt) continue;
        if (xs == xt && (xt == 0 || xt == n)) continue;
        if (ys == yt && (yt == 0 || yt == m)) continue;

        if (xs == xt) {
          if (ys > yt) swap(ys, yt);

          for (int j = ys; j < yt; j++) {
            int u = getPos(xt - 1, j);
            int v = getPos(xt, j);
            dis[u][v] = dis[v][u] = 0;
          }
        } else {
          if (xs > xt) swap(xs, xt);

          for (int i = xs; i < xt; i++) {
            int u = getPos(i, yt);
            int v = getPos(i, yt - 1);
            dis[u][v] = dis[v][u] = 0;
          }
        }
      }
    
    DSU dsu(N + 1);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int cur = getPos(i, j);
        {
          int x = i - 1, y = j;
          if (x >= 0 && x < n && y >= 0 && y < m) {
            int now = getPos(x, y);
            if (dis[cur][now]) dsu.merge(cur, now);
            dis[cur][now] = dis[now][cur] = 0;
          }
        }
        {
          int x = i + 1, y = j;
          if (x >= 0 && x < n && y >= 0 && y < m) {
            int now = getPos(x, y);
            if (dis[cur][now]) dsu.merge(cur, now);
            dis[cur][now] = dis[now][cur] = 0;
          }
        }
        {
          int x = i, y = j - 1;
          if (x >= 0 && x < n && y >= 0 && y < m) {
            int now = getPos(x, y);
            if (dis[cur][now]) dsu.merge(cur, now);
            dis[cur][now] = dis[now][cur] = 0;
          }
        }
        {
          int x = i, y = j + 1;
          if (x >= 0 && x < n && y >= 0 && y < m) {
            int now = getPos(x, y);
            if (dis[cur][now]) dsu.merge(cur, now);
            dis[cur][now] = dis[now][cur] = 0;
          }
        }
      }
    }
    if (dsu.same(s, t)) ans = min(ans, q - __builtin_popcount(st));
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}