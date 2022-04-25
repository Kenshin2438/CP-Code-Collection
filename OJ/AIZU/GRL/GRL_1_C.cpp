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
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

const ll inf = (ll) 1e18;
const int N = (int) 1e2 + 10;

int n, m;
ll dis[N][N];

bool warshall_floyd() {
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dis[i][k] == inf || dis[k][j] == inf) continue;
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (dis[i][i] < 0) return true;
  }
  return false;
}

void SingleTest(int TestCase) {
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      dis[i][j] = inf;
    }
    dis[i][i] = 0;
  }
  for (int u, v; m--; ) {
    cin >> u >> v >> dis[u][v];
  }

  if (warshall_floyd()) {
    return cout << "NEGATIVE CYCLE\n", void();
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (dis[i][j] >= inf) cout << "INF";
      else cout << dis[i][j];

      cout << " \n"[j + 1 == n];
    }
  }
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
