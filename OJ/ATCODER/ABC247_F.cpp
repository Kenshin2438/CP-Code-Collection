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
#define all(a) a.begin(), a.end()

using db = double;
using ll = long long;

const int mod = 998244353;

struct DSU {
  vec<int> p, sz;
  DSU(int _) : p(_ + 1), sz(_ + 1, 1) { iota(all(p), 0); }
  int f(int _) { return _ == p[_] ? _ : p[_] = f(p[_]); }
  bool same(int u, int v) { return f(u) == f(v); }
  void unite(int u, int v) {
    u = f(u), v = f(v);
    if (u == v) return;
    p[f(u)] = f(v), sz[v] += sz[u];
  }
};

void SingleTest(int TestCase) {
  int n; cin >> n;
  DSU s(n);
  vec<int> p(n), q(n);
  for (auto &x : p) cin >> x;
  for (auto &x : q) cin >> x;
  for (int i = 0; i < n; i++) s.unite(p[i], q[i]);
  if (n == 1) return cout << 1, void();
  vec<int> dp(n + 1);
  dp[1] = 1, dp[2] = 3;
  for (int i = 3; i <= n; i++) {
    dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
  }
  ll ans = 1;
  for (int i = 1; i <= n; i++) {
    if (i == s.f(i)) ans = ans * dp[s.sz[i]] % mod;
  }
  cout << ans;
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
