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
  int n; cin >> n;
  string s = to_string(n);

  int ans = 0;
  for (int i = 1; i <= 9; i++) {
    if (n % i == 0) ans += count(all(s), '0' + i);
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
