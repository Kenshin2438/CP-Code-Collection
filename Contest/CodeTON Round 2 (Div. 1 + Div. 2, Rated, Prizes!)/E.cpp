#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int mod = 998244353;

void solve() {
  int n, m; cin >> n >> m;
  vector<ll> val(n);
  for (ll &x : val) cin >> x;
  vector<vector<int>> G(n), rG(n);
  vector<int> d(n), rd(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    G[u].emplace_back(v);
    d[v] += 1;

    rG[v].emplace_back(u);
    rd[u] += 1;
  }
  auto toposort = [](const auto &G, auto d) -> vector<int> {
    queue<int> Q;
    for (int i = 0; i < (int)d.size(); i++) {
      if (d[i] == 0) Q.push(i);
    }
    vector<int> topo;
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      topo.emplace_back(u);
      for (const int &v : G[u]) {
        if (--d[v] == 0) Q.push(v);
      }
    }
    return topo;
  };
  auto topo = toposort(G, d);
  auto rtopo = toposort(rG, rd);
  ll ans = 0;
  for (int tt = 2005; tt--; ) {
    if (count(all(val), 0) == n) break;
    for (const int &u : rtopo) {
      if (val[u]) val[u] -= 1;
      for (const int &v : rG[u]) {
        if (val[v]) val[u] += 1;
      }
    }
    ans = (ans + 1) % mod;
  }
  for (const int &u : topo) {
    for (const int &v : G[u]) {
      val[v] = (val[v] + val[u]) % mod;
    }
  }
  cout << (ans + val[topo.back()]) % mod << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
