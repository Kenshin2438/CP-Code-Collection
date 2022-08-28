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
  ll a, b, c, d; cin >> a >> b >> c >> d;

  int ans = -1;

  if (a * d == b * c) ans = 0;
  else {
    ll A = a * d, B = b * c;
    if (A > B) swap(A, B); // A < B
    if (A == 0 || B % A == 0) ans = 1;
    else ans = 2;
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
