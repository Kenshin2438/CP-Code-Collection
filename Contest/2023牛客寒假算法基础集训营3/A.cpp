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
  ll ans = 0;
  
  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (x < 0) ans += x;
    else {
      if (x & 1) ans += x;
      else ans += 1;
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}