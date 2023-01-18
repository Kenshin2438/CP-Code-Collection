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
  int n; cin >> n;
  vector<int> a, b;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (x < 0) {
      a.emplace_back(x);
    } else {
      b.emplace_back(x);
    }
  }
  ll SA = abs(accumulate(all(a), 0LL));
  ll SB = abs(accumulate(all(b), 0LL));
  ll ans = SA * (sz(a) - 1) + SB * (sz(b) - 1) + SA * sz(b) + SB * sz(a);
  ans = 2 * (ans + SA + SB);
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}