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
  ll n, m, x, y, d;
  cin >> n >> m >> x >> y >> d;

  bool ok = true;
  {
    ll lx = x - d, rx = x + d;
    ll ly = y - d, ry = y + d;

    if (lx <= 1 && ly <= 1) ok = false;
    if (rx >= n && ry >= m) ok = false;
    if (lx <= 1 && rx >= n) ok = false;
    if (ly <= 1 && ry >= m) ok = false;
  }

  if (ok) cout << n + m - 2 << '\n';
  else cout << -1 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
