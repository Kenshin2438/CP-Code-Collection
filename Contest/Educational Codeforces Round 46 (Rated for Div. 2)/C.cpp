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

  vector<pair<ll, int>> pos;
  for (int i = 0; i < n; i++) {
    ll l, r; cin >> l >> r;
    pos.emplace_back(l, 1);
    pos.emplace_back(r + 1, -1);
  }
  sort(all(pos));

  vector<ll> ans(n + 1);
  for (ll pre = pos[0].first, num = 0, i = 0; i < sz(pos); i++) {
    auto [p, d] = pos[i];
    ans[num] += p - pre, pre = p;
    num += d;
  }

  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
