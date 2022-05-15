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
  int n, m; cin >> n >> m;
  vec<vec<bool>> edge(n, vec<bool>(n, false));
  for (int u, v, _ = 0; _ < m; _++) {
    cin >> u >> v, --u, --v;
    edge[u][v] = edge[v][u] = true;
  }
  vec<vec<ll>> dp(n, vec<ll>(1 << n, 0));
  for (int i = 0; i < n; i++) dp[i][1 << i] = 1;
  ll ans = 0;
  for (int s = 0; s < SZ(dp[0]); s++) {
    int low = s & -s;
    for (int u = 0; u < n; u++) {
      if (low > (1 << u) || dp[u][s] == 0) continue;
      for (int v = 0; v < n; v++) {
        if (edge[u][v] == false || low > (1 << v)) continue;
        if (s >> v & 1) {
          ans += dp[u][s] * (low == (1 << v));
        } else {
          dp[v][s | (1 << v)] += dp[u][s];
        }
      }
    }
  }
  cout << (ans - m) / 2 << '\n';
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
