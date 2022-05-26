#define PROBLEM "http://oj.daimayuan.top/course/10/problem/505"

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
#define pb push_back
#define all(a) a.begin(), a.end()

using db = long double;
using ll = long long;

const int N = (int) 1e5 + 10;

int n, sz[N], p[N];
vec<int> G[N];

void dfs(int u, int fa) {
  sz[u] = 1, p[u] = fa;
  for (int v : G[u]) {
    if (v == fa) continue;
    dfs(v, u);
    sz[u] += sz[v];
  }
}

void SingleTest(int TestCase) {
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v, w; cin >> u >> v >> w;
    G[u].pb(v), G[v].pb(u);
  }
  dfs(1, 0);
  ll ans = 0;
  for (int u = 1; u <= n; u++) {
    if ((int) G[u].size() < 3) continue;

    vec<int> val;
    for (int v : G[u]) {
      if (v != p[u]) val.pb(sz[v]);
    }
    val.pb(n - accumulate(all(val), 0) - 1);
    array<ll, 4> dp = {1, 0, 0, 0};
    for (int x : val) {
      for (int i = 3; i >= 1; i--) {
        dp[i] += dp[i - 1] * x;
      }
    }
    ans += dp[3];

    debug(dp);
    debug(val);
  }
  cout << ans;
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
