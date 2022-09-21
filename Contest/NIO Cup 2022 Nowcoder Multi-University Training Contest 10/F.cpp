#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n, m, s, t; cin >> n >> m >> s >> t;
  --s, --t;
  vector<vector<int>> G(n);
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    --u, --v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  vector<int> cnt(n, 0);
  vector<bool> win(n, false);

  queue<int> Q;
  Q.push(t), win[t] = true;
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    debug(u);
    for (const int &v : G[u]) {
      cnt[v] += 1;
      if (cnt[v] >= 2 && win[v] == false) {
        win[v] = true; Q.push(v);
      }
    }
  }
  cout << (win[s] ? "Join Player" : "Cut Player") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
