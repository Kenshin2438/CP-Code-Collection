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
  ll x1, y1; cin >> x1 >> y1;
  ll x2, y2; cin >> x2 >> y2;
  assert(0 <= x1 && x1 <= (int) 1e9);
  assert(0 <= x2 && x2 <= (int) 1e9);
  assert(0 <= y1 && y1 <= (int) 1e9);
  assert(0 <= y2 && y2 <= (int) 1e9);
  assert(!(x1 == x2 && y1 == y2));

  cout << ((x2 - x1) == (y2 - y1) && x2 > x1 ? "GG" : "YUUMI") << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  assert(1 <= T && T <= 10000);
  while (T--) solve();

  return 0;
}