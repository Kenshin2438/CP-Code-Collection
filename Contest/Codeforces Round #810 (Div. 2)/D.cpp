#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const ll INF = 1e18;

void solve() {
  int n, m; cin >> n >> m;
  vector<pair<ll, ll>> p;
  vector<int> x(n), h(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> h[i];
    p.emplace_back(x[i] - h[i] + 1, 1);
    p.emplace_back(x[i] + 1, -2);
    p.emplace_back(x[i] + h[i] + 1, 1);
  }
  p.emplace_back( INF, 0);
  p.emplace_back(-INF, 0);
  sort(all(p));
  ll Mi = INF, Mx = -INF, D = 0, pre = 0;
  for (int i = 1; i + 1 < (int) p.size(); i++) {
    D += p[i].second;
    if (p[i].first != p[i + 1].first) {
      if (pre + D > m) {
        Mx = max(Mx, p[i].first + pre + D - m);
        Mi = min(Mi, p[i].first - pre - D + m);
      }
    }
    if (p[i].first != p[i - 1].first) {
      if (pre > m) {
        Mx = max(Mx, p[i].first - 1 + pre - m);
        Mi = min(Mi, p[i].first - 1 - pre + m);
      }
    }
    pre += D * (p[i + 1].first - p[i].first);
  }
  for (int i = 0; i < n; i++) {
    cout << int((x[i] + h[i]) >= Mx && (x[i] - h[i]) <= Mi);
  }
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
