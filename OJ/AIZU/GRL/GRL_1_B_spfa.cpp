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

void SingleTest(int TestCase) {
  cin >> n >> m;
  G.resize(n);
  int s; cin >> s;
  for (int u, v, d; m--; ) {
    cin >> u >> v >> d;
    G[u].emplace_back(v, d);
  }
  if (spfa(s)) {
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
