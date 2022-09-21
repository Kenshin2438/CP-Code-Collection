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
  int n, x, y; cin >> n >> x >> y;
  if (x > y) swap(x, y);
  // debug(x, y);
  if (x > 0 || y == 0) return cout << "-1\n", void();
  if ((n - 1) % y) return cout << "-1\n", void();
  for (int now = 1, cnt = 0, i = 2; i <= n; i++) {
    if (cnt < y) cnt += 1;
    else cnt = 1, now = i;
    cout << now << " \n"[i == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
