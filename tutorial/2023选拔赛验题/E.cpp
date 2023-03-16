#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  int n, m, q; cin >> n >> m >> q;
  assert(1 <= n && n <= 600);
  assert(1 <= m && m <= (int) 1e3);
  assert(1 <= q && q <= (int) 1e5);

  static constexpr int inf = 0x3f3f3f3f;
  vector<vector<int>> dis(n, vector<int>(n, inf));
  for (int i = 0; i < n; i++) dis[i][i] = 0;

  for (int _ = 0; _ < m; _++) {
    int u, v, w; cin >> u >> v >> w;
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    assert(1 <= w && w <= (int) 1e6);
    --u, --v;
    dis[u][v] = min(dis[u][v], w);
  }

  for (int k = 0; k < n; k++) {
    for (int u = 0; u < n; u++) {
      for (int v = 0; v < n; v++) {
        dis[u][v] = min(dis[u][v], dis[u][k] + dis[k][v]);
      }
    }
  }

  for (int _ = 0; _ < q; _++) {
    int u, v; cin >> u >> v;
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    --u, --v;
    cout << (dis[u][v] >= inf ? -1 : dis[u][v]) << "\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}