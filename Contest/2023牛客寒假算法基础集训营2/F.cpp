#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  int n, k; cin >> n >> k;
  vector<array<int, 3>> grid(n, {0, 0, 0});
  for (int i = 0; i < k; i++) {
    int x, y; cin >> x >> y;
    grid[x - 1][y - 1] ^= 1;
  }
  vector<array<int, 3>> ok(n, {0, 0, 0});
  vector<array<int, 3>> vis(n, {0, 0, 0});
  const function<int(int, int)> f = [&](int x, int y) {
    if (vis[x][y]) return ok[x][y];
    vis[x][y] = 1;
    if (x == n - 1 && y == 2) return ok[x][y] = 1;
    if (grid[x][y] == 1) return 0;
    if (x == n - 1) return ok[x][y] = f(x, y + 1);
    if (y == 2) return ok[x][y] = f(x + 1, y);
    return ok[x][y] = f(x + 1, y) | f(x, y + 1);
  };
  f(0, 0);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      // cout << ok[i][j] << " \n"[j == 2];
      ans += ok[i][j];
    }
  }
  cout << ans - ok[0][0] << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}