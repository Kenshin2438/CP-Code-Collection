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

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  vector<vector<int>> ans(n, vector<int>(n));
  for (int i = 0; i < n; i++) ans[i][i] = a[i];

  for (int i = 0; i < n; i++) {
    for (int j = i - 1; j >= 0; j--) {
      ans[i][j] = (ans[i][j + 1] - i + n) % n;
    }
    for (int j = i + 1; j < n; j++) {
      ans[i][j] = (ans[i][j - 1] + i) % n;
    }
  }

  for (const auto &v : ans) {
    for (const int &x : v) cout << x << ' ';
    cout << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
