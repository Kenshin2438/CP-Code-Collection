#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  int x, y, xp, yp;
  cin >> x >> y >> xp >> yp;
  if (xp <= x && yp <= y) {
    cout << (double) max(xp, x - xp) * max(yp, y - yp) / (x * y) << '\n';
  } else if (xp <= x) {
    double ans = 0;
    for (int xs = 0; xs <= x; xs++) {
      int dx = abs(xs - xp);
      ans = max(ans, (double) (dx * y) / (x * y + dx * (yp - y)));
    }
    cout << ans << '\n';
  } else if (yp <= y) {
    double ans = 0;
    for (int ys = 0; ys <= y; ys++) {
      int dy = abs(ys - yp);
      ans = max(ans, (double) (dy * x) / (x * y + dy * (xp - x)));
    }
    cout << ans << '\n';
  } else {
    double ans = 0;
    for (int xs = 0; xs <= x; xs++) {
      int dx = x - xs;
      int Dx = xp - x;
      ans = max(ans, (double) (dx * y) / (x * y + dx * (yp - y) + Dx * yp));
    }
    cout << ans << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}