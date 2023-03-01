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
  vector<ll> h(n);
  for (ll &x : h) cin >> x;

  const auto f = [&](ll l, ll r) {
    return (l + r) * (r - l + 1) / 2;
  };    
  auto calc = [&]() -> vector<ll> {
    vector<ll> leftCost(n);

    vector<pair<ll, ll>> seg;
    seg.emplace_back(-1LL, -1LL);
    seg.emplace_back(h[0], h[0]);

    for (int i = 1; i < n; i++) {
      if (h[i] > h[i - 1]) {
        leftCost[i] = leftCost[i - 1];
        if (h[i] == seg.back().second + 1) {
          seg.back().second = h[i];
        } else {
          seg.emplace_back(h[i], h[i]);
        }
      } else {
        leftCost[i] = leftCost[i - 1];
        ll l = h[i], r = h[i];
        while (seg.back().second >= l) {
          auto P = seg.back(); 
          seg.pop_back();
          
          int nr = max(0LL, l - 1);
          int nl = max(0LL, nr - (P.second - P.first + 1) + 1);

          leftCost[i] += f(P.first, P.second) - f(nl, nr);
          l = nl;
        }
        seg.emplace_back(l, r);
      }
    }
    return leftCost;
  };

  auto a = calc();
  reverse(all(h));
  auto b = calc();

  reverse(all(h));
  reverse(all(b));

  // debug(a);
  // debug(b);

  ll ans = 1e18;
  for (int i = 0; i < n; i++) {
    ans = min(ans, a[i] + h[i] + b[i]);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}