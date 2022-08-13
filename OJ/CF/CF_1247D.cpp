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

  ll ans = 0;
  map<vector<pair<int, int>>, int> cnt;
  for (int x, i = 0; i < n; i++) {
    cin >> x;
    vector<pair<int, int>> pf, S;
    for (int j = 2; j * j <= x; j++) {
      if (x % j) continue;
      int e = 0;
      while (x % j == 0) x /= j, e += 1;
      if (e %= k) {
        pf.emplace_back(j, k - e);
        S.emplace_back(j, e);
      }
    }
    if (x != 1) {
      pf.emplace_back(x, k - 1);
      S.emplace_back(x, 1);
    }

    sort(all(S)), sort(all(pf));

    ans += cnt[pf];
    cnt[S] += 1;
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
