#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

int mat[55][55];

void solve() {
  int n, m; cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    if (i % 4 == 1 || i % 4 == 0) {
      int a[] = {1, 0, 0, 1};
      for (int j = 1; j <= m; j++) {
        mat[i][j] = a[(j - 1) % 4];
      }
    } else {
      int a[] = {0, 1, 1, 0};
      for (int j = 1; j <= m; j++) {
        mat[i][j] = a[(j - 1) % 4];
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cout << mat[i][j] << " \n"[j == m];
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T; cin >> T;
  while (T--) solve();
  return 0;
}