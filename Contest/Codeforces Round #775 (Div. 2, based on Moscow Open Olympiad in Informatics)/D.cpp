#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n; cin >> n;
  int m; cin >> m;
  vector<bool> vis(m + 1, false);
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    vis[x] = true;
  }
  vector<int> d(m + 2, 0);
  for (int i = 1; i <= m; i++) if (vis[i] == false) {
    for (int j = 1; j * 1LL * i <= m; j++) if (vis[j] == true) {
      int l = j * i, r = min(m, i * j + j - 1);
      d[l] += 1, d[r + 1] -= 1;
    }
  }
  bool ans = true;
  for (int i = 1; i <= m; i++) {
    d[i] += d[i - 1];
    if (d[i] && vis[i]) ans = false;
  }
  cout << (ans ? "Yes" : "No") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
