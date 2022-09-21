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
  vector<array<int, 5>> ops(n);

  vector<int> XS, YS;
  for (auto &&[x1, y1, x2, y2, c] : ops) {
    cin >> x1 >> y1 >> x2 >> y2 >> c;
    XS.emplace_back(x1), XS.emplace_back(x2);
    YS.emplace_back(y1), YS.emplace_back(y2);
  }
  sort(all(XS)), XS.erase(unique(all(XS)), end(XS));
  sort(all(YS)), YS.erase(unique(all(YS)), end(YS));

  for (auto &&[x1, y1, x2, y2, c] : ops) {
    x1 = lower_bound(all(XS), x1) - begin(XS);
    x2 = lower_bound(all(XS), x2) - begin(XS);
    y1 = lower_bound(all(YS), y1) - begin(YS);
    y2 = lower_bound(all(YS), y2) - begin(YS);
  }
  reverse(all(ops));

  int ans = 0;
  vector<bool> vis(n, false);
  for (int i = 0; i < sz(XS); i++) {
    vector<int> p(sz(YS) + 1); iota(all(p), 0);
    const function<int(int)> nxt = [&](int x) {
      return x == p[x] ? x : p[x] = nxt(p[x]);
    };
    for (const auto &[x1, y1, x2, y2, c] : ops) {
      if (x1 <= i && i < x2) {
        for (int y = nxt(y2); y < y1; y = nxt(y)) {
          p[nxt(y)] = p[nxt(y + 1)];
          if (vis[c] == false) vis[c] = true, ans += 1;
        }
      }
    }
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
