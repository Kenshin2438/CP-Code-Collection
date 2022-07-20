#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n, m, S, K;
  cin >> n >> m >> S >> K;
  --S;

  vector<vector<array<int, 3>>> G(n); // {to, dist, tag}
  for (int i = 0; i < m; i++) {
    int x, y, w, op;
    cin >> x >> y >> w >> op;
    --x, --y;
    G[x].push_back({y, w, op});
  }

  const ll inf = 1e18;

  vector<array<ll, 2>> dis(n, {inf, inf});
  priority_queue<array<ll, 3>> pq; // {dist, node, tag}
  set<int> P;
  for (int i = 0; i < n; i++) P.insert(i);

  dis[S][0] = 0; 
  pq.push({0, S, 0});

  while (!pq.empty()) {
    ll D = -pq.top()[0];
    int u = pq.top()[1];
    int op = pq.top()[2];
    pq.pop();

    debug(u, D, op);
    if (D > dis[u][op]) continue;

    if (op == 0) { 
      P.erase(u);
      for (const auto &a : G[u]) {
        int v = a[0], w = a[1], tag = a[2];
        if (dis[v][tag] > dis[u][0] + w) {
          dis[v][tag] = dis[u][0] + w;
          pq.push({-dis[v][tag], v, tag});
        }
      }
    } else { // op == 1
    vector<bool> is(n, false);
      for (const auto &a : G[u]) {
        int v = a[0], w = a[1], tag = a[2];
        if (dis[v][tag] > dis[u][1] + w - K) {
          dis[v][tag] = dis[u][1] + w - K;
          pq.push({-dis[v][tag], v, tag});
        }
        is[v] = true;
      }
      for (const int &v : P) {
        if (is[v]) continue;
        if (dis[v][0] > dis[u][1]) {
          dis[v][0] = dis[u][1];
          pq.push({-dis[v][0], v, 0});
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    ll D = min(dis[i][0], dis[i][1]);
    if (D == inf) D = -1;
    cout << D << " ";
  }
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();
  
  return 0;
}