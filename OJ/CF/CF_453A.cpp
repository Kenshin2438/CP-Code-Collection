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
  int n, m; cin >> m >> n;
  double ans = m;
  for (int i = 1; i < m; i++) ans -= pow(i * 1. / m, n);
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
