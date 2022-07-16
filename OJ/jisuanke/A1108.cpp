#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n; cin >> n;
  vector<vector<int>> d(n, vector<int>(n));
  for (auto &&v : d) for (auto &&x : v) {
    cin >> x;
    if (x == -1) x = 0x3f3f3f3f;
  }
  
  ll ans = 0;
  function<void(int, int)> solve = [&](int l, int r) {
    if (l == r) {
      for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
          if (u == l || v == l) continue;
          ans += (d[u][v] == 0x3f3f3f3f ? -1 : d[u][v]);
        }
      }
      return;
    }
    int m = (l + r) >> 1;

    auto S = d;
    for (int k = m + 1; k <= r; k++) {
      for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
          if (u == k || v == k) continue;
          d[u][v] = min(d[u][k] + d[k][v], d[u][v]);
        }
      }
    }
    solve(l, m);

    d = S;
    for (int k = l; k <= m; k++) {
      for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
          if (u == k || v == k) continue;
          d[u][v] = min(d[u][k] + d[k][v], d[u][v]);
        }
      }
    }
    solve(m + 1, r);
  };
  solve(0, n - 1);
  cout << ans << '\n';
  return 0;
}