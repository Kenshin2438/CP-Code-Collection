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
  int n, m; cin >> n >> m;
  vector<ll> seg;

  {
    ll pre = 0;
    for (int i = 0; i < n; i++) {
      int x; cin >> x; seg.emplace_back(x - pre);
      pre = x;
    }
    seg.emplace_back(m - pre);
  }

  vector<array<ll, 2>> SUM(sz(seg) + 1);
  for (int i = 1; i < sz(SUM); i++) {
    SUM[i][0] = SUM[i - 1][0] + (~i & 1) * seg[i - 1];
    SUM[i][1] = SUM[i - 1][1] + ( i & 1) * seg[i - 1];
  }

  ll ans = SUM.back()[1];
  for (int i = 1; i < sz(SUM); i++) if (seg[i - 1] > 1) {
    ans = max(ans, seg[i - 1] - 1 + SUM[i - 1][1] + SUM.back()[0] - SUM[i][0]);
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
