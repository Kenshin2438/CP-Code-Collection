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
  ll x, y; cin >> x >> y;
  cout << 2LL * (x - y) << '\n';
  for (ll now = y; now <= x; now++) {
    cout << now << " ";
  }
  for (ll now = x - 1; now >= y + 1; now--) {
    cout << now << " ";
  }
  cout << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}