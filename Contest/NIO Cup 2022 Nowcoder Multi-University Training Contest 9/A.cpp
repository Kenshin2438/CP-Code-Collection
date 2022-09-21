#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) static_cast<int>(size(x))

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n, m; cin >> n >> m;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  vector<int> cnt(m + 1);
  int now = 0;
  ll ans = 0;
  for (int l = 0, r = 0; r < n; r++) {
    if (cnt[ a[r] ]++ == 0) now += 1;
    if (now == m) {
      while (l <= r) {
        if (cnt[ a[l] ] == 1) break;
        cnt[ a[l] ] -= 1, l += 1;
      }
      ans += (l + 1);
      debug(l);
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
