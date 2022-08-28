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
  int n, m; cin >> n >> m;

  int cnt = 0;

  vector<string> mat(n);
  for (auto &s : mat) {
    cin >> s;
    cnt += count(all(s), '1');
  }

  int ans = 4;
  for (int i = 0; i + 1 < n; i++) {
    for (int j = 0; j + 1 < m; j++) {
      ans = min(ans,
        (mat[i][j] == '1') + (mat[i][j + 1] == '1') + (mat[i + 1][j] == '1') + (mat[i + 1][j + 1] == '1')
      );
    }
  }

  cout << cnt - max(0, ans - 2) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
