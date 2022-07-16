#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> d(n, vector<int>(n, 0x3f3f3f3f));
  for (int i = 0; i < m; i++) {
    int u, v, w; cin >> u >> v >> w;
    d[u][v] = min(d[u][v], w);
  }
  for (int s, t, _ = 0; _ < 6; _++) {
    cin >> s >> t;
    for (int k = 0; k < n; k++) {
      for (int u = 0; u < n; u++) {
        if (k == u || d[u][k] == 0x3f3f3f3f) continue;
        for (int v = 0; v < n; v++) {
          if (u == v) continue;
          d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
        }
      }
    }
    cout << (d[s][t] = -d[t][s]) << '\n'; 
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  int T; cin >> T;
  while (T--) solve();

  return 0;
}