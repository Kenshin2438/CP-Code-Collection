#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

int n; double e[250][250][250];
double E(int x, int y, int z) {
  if (e[x][y][z] != -1) return e[x][y][z];
  double S = 0, U = 0;
  if (x >= 2) {
    S += E(x - 2, y + 2, z + 1) * x * (x - 1);
    U += x * (x - 1);
  }
  if (z >= 2) {
    S += E(x, y - 2, z - 2) * z * (z - 1) * 4;
    U += z * (z - 1) * 4;
  }
  if (x >= 1 && y - (2 * z) >= 1) {
    S += E(x - 1, y, z) * x * (y - 2 * z) * 2;
    U += x * (y - 2 * z) * 2;
  }
  if (x >= 1 && z >= 1) {
    S += E(x - 1, y, z - 1) * x * z * 4;
    U += x * z * 4;
  }
  if (y - z * 2 > 0 && z > 0) {
    S += E(x, y - 2, z - 1) * (y - 2 * z) * z * 4;
    U += (y - 2 * z) * z * 4;
  }
  if (y - 2 * z >= 2) {
    S += E(x, y - 2, z) * (y - 2 * z) * (y - 2 * z - 1);
    U += (y - 2 * z) * (y - 2 * z - 1);
  }
  return e[x][y][z] = U == 0 ? 0 : (S + n * n) / U;
}

void solve() {
  cin >> n;
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
      for (int k = 0; k <= n; k++)
        e[i][j][k] = -1;
  cout << E(n, 0, 0) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(9);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
