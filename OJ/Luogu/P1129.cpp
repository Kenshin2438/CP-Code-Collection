#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n; cin >> n;
  vector<vector<int>> g(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> g[i][j];
    }
  }
  vector<int> match(n * 2, -1);
  bitset<500> vis;
  const function<bool (int)> dfs = [&](int u) {
    for (int v = 0; v < n; v++) {
      if (g[u][v] == 0) continue;
      if (vis[v + n] == 0) {
        vis[v + n] = 1;
        if (match[v + n] == -1 || dfs(match[v + n])) {
          match[v + n] = u;
          return true;
        }
      }
    }
    return false;
  };
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    cnt += dfs(i);
    vis.reset();
  }
  cout << (cnt >= n ? "Yes" : "No") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  int T; cin >> T;
  while (T--) solve();

  return 0;
}