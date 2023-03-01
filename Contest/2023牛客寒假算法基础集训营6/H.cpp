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
  int x; cin >> x;
  int l, r; cin >> l >> r;
  auto U = [](int a, int b, int c, int d) {
    debug(a, b, c, d);
    return max(0, min(b, d) - max(a, c) + 1);
  };
  cout << 1 - double(U(x, r, l, r)) / (r - l + 1) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}