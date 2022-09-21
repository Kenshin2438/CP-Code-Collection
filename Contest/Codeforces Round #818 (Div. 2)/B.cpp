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
  int n, k, r, c; cin >> n >> k >> r >> c;
  r = (r - 1) % k, c = (c - 1) % k;
  auto chk = [&](int x, int y) -> bool {
    x %= k, y %= k;
    return (x + y) % k == (r + c) % k;
  };
  vector<string> mat(n, string(n, '.'));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (chk(i, j)) mat[i][j] = 'X';
    }
  }
  for (const auto &s : mat) cout << s << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
