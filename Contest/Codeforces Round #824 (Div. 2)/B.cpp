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
  vector<int> a(n);
  for (int &x : a) cin >> x;

  ll ans = 0;
  if (a[0] == 1) {
    ans = accumulate(all(a), 0LL) - n;
  } else {
    for (int i = 1; i < n; i++) {
      if (a[i] < 2 * a[0]) continue;
      int r = a[i] % (2 * a[0] - 1);
      ans += a[i] / (2 * a[0] - 1) - (r == 0);
    }
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
