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
  int n, ans = 0; cin >> n;

  array<int, 2> xs{0, 0}, ys{0, 0};
  for (int i = 1; i <= n; i++) {
    int x, y; cin >> x >> y;
    if (x == 0) {
      if (y < 0) ys[1] = min(ys[1], y);
      if (y > 0) ys[0] = max(ys[0], y);
    }
    if (y == 0) {
      if (x < 0) xs[1] = min(xs[1], x);
      if (x > 0) xs[0] = max(xs[0], x);
    }
  }
  ans = abs(xs[0]) + abs(xs[1]) + abs(ys[0]) + abs(ys[1]);
  cout << ans * 2 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
