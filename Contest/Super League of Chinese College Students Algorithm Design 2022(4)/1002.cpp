#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int N = 2e5 + 100;

int n, m;
vector<int> G[N], E[N], P[N];

int dfn[N], low[N], idx, s[N], tp, in[N];
int scc[N], sc, sz[N];

void tarjan(int u) {
  dfn[u] = low[u] = ++idx, s[++tp] = u, in[u] = 1;
  for (int v : G[u]) {
    if (dfn[v] == 0) tarjan(v), low[u] = min(low[u], low[v]);
    else if (in[v]) low[u] = min(low[u], dfn[v]);
  }
  if (low[u] == dfn[u]) {
    sc++;
    while (s[tp + 1] != u) {
      sz[scc[s[tp]] = sc]++, in[s[tp--]] = 0;
    }
  }
}

void solve() {
  
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
