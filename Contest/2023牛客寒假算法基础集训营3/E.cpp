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
  ll xa, xb, ya, yb;
  cin >> xa >> ya;
  cin >> xb >> yb;

  ll X = (xa + xb) - (yb - ya);
  ll Y = (ya + yb) + (xb - xa);
  if (X % 2 == 0 && Y % 2 == 0) {
    cout << X / 2 << " " << Y / 2 << "\n";
  } else {
    cout << "No Answer!\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}