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

const int N = (int) 500 + 10;

int n, m, g[N][N], d[N], ans[N];

void SingleTest(int TestCase) {
  cin >> n >> m;
  for (int u, v; m--; ) {
    cin >> u >> v;
    g[u][v] = g[v][u] = 1;
    d[u]++, d[v]++;
  }
  for (int i = 1; i <= n; i++) {
    ans[i] = -1;
    if (d[i] + 1 == n) ans[i] = 1;
  }
  for (int i = 1; i <= n; i++) {
    if (ans[i] == 1) continue;
    stack<int> dfs; dfs.push(i);
    if (ans[i] == -1) ans[i] = 0;
    while (!dfs.empty()) {
      int u = dfs.top(); dfs.pop();
      for (int v = 1; v <= n; v++) {
        if (g[u][v] == 1 || v == u) continue;
        if (ans[v] == -1) {
          ans[v] = ans[u] ^ 0 ^ 2;
          dfs.push(v);
        } else if (ans[v] == ans[u]) {
          return cout << "No", void();
        }
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (g[i][j] && abs(ans[i] - ans[j]) == 2) {
        return cout << "No", void();
      }
    }
  }

  cout << "Yes\n";
  for (int i = 1; i <= n; i++) cout << char('a' + ans[i]);
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
