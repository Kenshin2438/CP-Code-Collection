#define PROBLEM "http://oj.daimayuan.top/course/10/problem/437"

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
  #include "debug.hpp"
#else
  #define debug(...)
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(), a.end()

typedef double db;
typedef long long ll;

void SingleTest(int TestCase) {
  const int inf = 0x3f3f3f3f;

  int n, m, k; cin >> n >> k >> m;
  vec<array<int, 3>> g(m);
  // for (auto &[u, v, c] : g) cin >> v >> u >> c, --v, --u;
  for (int i = 0; i < m; i++) {
    cin >> g[i][1] >> g[i][0] >> g[i][2];
    --g[i][1], --g[i][0];
  }
  vec<vec<int>> dp(n, vec<int>(n, inf));
  for (int i = 0; i < n; i++) dp[i][i] = 0;
  while (--k) {
    vec<vec<int>> n_dp(n, vec<int>(n, inf));
    // for (auto [u, v, c] : g) {
    for (int o = 0; o < m; o++) {
      int u = g[o][0], v = g[o][1], c = g[o][2];
      if (u == v) continue;

      if (u > v) {
        for (int i = v + 1; i < n; i++) {
          n_dp[v][max(u, i)] = min(n_dp[v][max(u, i)], dp[u][i] + c);
        }
      } else {
        for (int i = 0; i < v; i++) {
          n_dp[v][min(u, i)] = min(n_dp[v][min(u, i)], dp[u][i] + c);
        }
      }
    }
    dp = move(n_dp);
  }
  int ans = inf;
  for (int i = 0; i < n; i++) ans = min(ans, *min_element(all(dp[i])));
  cout << (ans >= inf ? -1 : ans);
}

void init() { }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--; ) SingleTest(++TestCase);
  return 0;
}
