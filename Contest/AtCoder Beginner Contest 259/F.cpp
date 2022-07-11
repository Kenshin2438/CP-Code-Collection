#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int N = (int) 3e5 + 10;

int n, d[N];
vector<pair<int, ll>> G[N];
vector<ll> dp[N];

void dfs(int u, int fa) {
  dp[u].resize(d[u] + 1, 0LL);

  vector<ll> s;
  for (auto P : G[u]) {
    int v = P.first;
    if (v == fa) continue;
    dfs(v, u);

    ll w = P.second;
    dp[u][0] += dp[v][ d[v] ];
    if (d[v] == 0) {
      s.push_back(0LL);
    } else {
      s.push_back(dp[v][d[v] - 1] + w - dp[v][d[v]]);
    }
  } 
  sort(all(s), greater<ll>());
  int p = 0, sz = s.size();
  for (int i = 1; i <= d[u]; i++) {
    dp[u][i] = dp[u][i - 1];
    if (p < sz) {
      dp[u][i] = max(dp[u][i], dp[u][i] + s[p]);
      p++;
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> d[i];
  for (int i = 1; i < n; i++) {
    int u, v, w; 
    cin >> u >> v >> w;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  for (int i = 1; i <= n; i++) {
    d[i] = min(d[i], (int) G[i].size());
  }
  int rt = 1;
  dfs(rt, 0);
  cout << *max_element(all(dp[rt])) << '\n';
  return 0;
}


/**

[l, r]

[1, 1] -> 1
[2, 3] -> 2
[2, 5] 
[3, 4] 
[5, 5] 

[1, 1] -> 1
[2, 3] -> 2
[3, 5]
[3, 4] -> 3
[5, 5]

**/