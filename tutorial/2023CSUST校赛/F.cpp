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
  assert(1 <= n && n <= 300);

  vector<pair<ll, ll>> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i].first >> p[i].second;
  }

  constexpr ll inf = (ll) 1E18L;
  vector<unordered_map<int, ll>> DP(n);
  const function<ll(int, int)> dp = [&](int l, int r) {
    if (DP[l].find(r) != end(DP[l])) return DP[l][r];
    auto & res = DP[l][r] = inf;
    if (r - l == 1) return res = 0LL;
    if (r - l == 2) {
      res = p[l].first * p[l].second * p[r - 1].second;
      return res;
    }
    for (int k = l + 1; k < r; k++) {
      ll cost = p[l].first * p[r - 1].second * p[k].first;
      res = min(res, dp(l, k) + dp(k, r) + cost);
    }
    return res;
  }; // [l, r)
  cout << dp(0, n) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}