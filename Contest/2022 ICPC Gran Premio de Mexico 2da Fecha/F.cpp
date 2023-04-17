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
  vector<pair<ll, ll>> pts(n);
  for (auto &&[x, y] : pts) cin >> x >> y;

  const auto check = [&](int i, int j, int k) -> bool {
    return (pts[k].second - pts[i].second) * (pts[j].first - pts[i].first) 
        == (pts[j].second - pts[i].second) * (pts[k].first - pts[i].first);
  };

  int ans = n * (n - 1) * (n - 2) * (n - 3) / (4 * 3 * 2);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j + 1; k < n; k++) {
        for (int h = k + 1; h < n; h++) {
          if (check(i, j, k) or
              check(i, j, h) or
              check(i, h, k) or
              check(h, j, k)) {
            ans -= 1;
          }
        }
      }
    }
  }
  cout << ans << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}