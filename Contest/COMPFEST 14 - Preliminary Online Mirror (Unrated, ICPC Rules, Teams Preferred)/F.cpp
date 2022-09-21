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
  vector<pair<int, int>> p(n);
  for (auto &&[l, r] : p) cin >> l >> r;

  vector<int> ans(30);
  for (int i = 0; i < sz(ans); i++) {
    int len = 1 << i;

    vector<pair<int, int>> D;
    for (const auto &[l, r] : p) {
      if (r - l + 1 >= len) ans[i] += 1;
      else {
        int pl = l % len, pr = r % len;
        if (pl <= pr) {
          D.emplace_back(pl, 1);
          D.emplace_back(pr + 1, -1);
        } else {
          D.emplace_back(0, 1);
          D.emplace_back(pr + 1, -1);
          D.emplace_back(pl, 1);
          D.emplace_back(len, -1);
        }
      }
    }
    sort(all(D));

    int M = 0, V = 0;
    for (const auto &[ignore, val] : D) {
      M = max(M, V += val);
    }
    ans[i] += M;
  }

  int q; cin >> q;
  for (int W; q--; ) {
    cin >> W;
    cout << ans[__builtin_ctz(W)] << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
