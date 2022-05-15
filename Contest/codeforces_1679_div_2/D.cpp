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
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

void SingleTest(int TestCase) {
  ll n, m, k; cin >> n >> m >> k;
  vec<int> val(n);
  vec<PII> edge(m);
  for (int & x : val) cin >> x;
  if (m == 0) {
    if (k == 1) cout << *min_element(all(val)) << '\n';
    else cout << -1 << '\n';
    return ;
  }
  for (auto &&[u, v] : edge) {
    cin >> u >> v;
    u--, v--;
  }
  ll l = 0, r = 1e9, ans = -1;
  while (l <= r) {
    ll m = (l + r) >> 1;
    vec<vec<int>> G(n);
    vec<int> deg(n, 0);
    for (auto [u, v] : edge) {
      if (val[u] <= m && val[v] <= m) {
        G[u].push_back(v);
        deg[v]++;
      }
    }
    vec<int> topo;
    queue<int> q;
    for (int i = 0; i < n; i++) {
      if (deg[i] == 0) q.push(i);
    }
    while (not q.empty()) {
      int u = q.front(); q.pop();
      topo.push_back(u);
      for (int v : G[u]) {
        if (--deg[v] == 0) q.push(v);
      }
    }
    if (SZ(topo) != n) {
      ans = m, r = m - 1;
      continue;
    }
    // SSSP on DAG
    vec<int> dis(n, 0);
    for (int u : topo) {
      for (int v : G[u]) {
        dis[v] = dis[u] + 1;
      }
    }
    if (*max_element(all(dis)) >= k - 1) {
      ans = m, r = m - 1;
    } else {
      l = m + 1;
    }
  }
  cout << ans << '\n';
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
