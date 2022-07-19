#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

/**
 *  1  2  3  4  5 
 *  1  2  3  4  5 
 */

void solve() {
  int n, l, r; cin >> n >> l >> r;
  vector<int> ans(n + 1, 0);
  bool ok = true;
  for (int i = 1; i <= n; i++) {
    int x = (r / i) * i;
    if (x < l) ok = false;
    ans[i] = x;
  }
  if (ok) {
    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " \n"[i == n];
    }
  } else cout << "NO\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}