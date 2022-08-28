#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n, k; cin >> n >> k;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  static const auto chk = [&](int m) -> bool {
    auto b = a;

    /**
    max{d(u, v)} 上界: 2 * min_element(); 下界: min(val[i], val[i + 1])
    **/

    int cnt = 0;
    for (int &x : b) if (x * 2 < m) cnt += 1, x = 1e9;
    for (int i = 1; i < n; i++) {
      if (min(b[i], b[i - 1]) >= m) break;
      if (i + 1 == n) {
        if (*max_element(all(b)) < m) cnt += 2;
        else cnt += 1;
      }
    }

    return cnt <= k;
  };

  int l = 1, r = 1e9, ans = -1;
  while (l <= r) {
    int m = (l + r) >> 1;
    if (chk(m)) l = m + 1, ans = m;
    else r = m - 1;
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
