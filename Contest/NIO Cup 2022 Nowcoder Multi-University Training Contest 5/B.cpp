#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  for (int n, m; cin >> n >> m;) {
    vector<ll> a(n);
    for (ll &x : a) cin >> x;

    int l = 1, r = n, ans = 0;
    while (l <= r) {
      ll k = (l + r) >> 1;
      vector<ll> b(n);
      for (int i = 1; i <= n; i++) {
        b[i - 1] = a[i - 1] + k * i;
      }
      sort(all(b));
      partial_sum(all(b), begin(b));

      if (m >= b[k - 1]) ans = k, l = k + 1;
      else r = k - 1;
    }
    cout << ans << '\n';
  }

  return 0;
}
