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
  vector<pair<int, int>> seg(n);
  for (auto &&[l, r] : seg) {
    cin >> l >> r;
  }
  seg.emplace_back(-1, -1);
  sort(all(seg));

  vector<int> len(sz(seg));
  for (int i = 0; i < sz(seg); i++) {
    len[i] = seg[i].second - seg[i].first;
  }
  partial_sum(all(len), begin(len));

  int q; cin >> q;
  for (int x, a; q--;) {
    cin >> x >> a;
    int l = max(1, x - a), r = x, ans = 0;

    static const int inf = numeric_limits<int>::max();
    int pR = prev(upper_bound(all(seg), pair<int, int>{r, inf})) - begin(seg);
    ans += len[pR] - max(0, seg[pR].second - r);
    int pL = prev(upper_bound(all(seg), pair<int, int>{l, inf})) - begin(seg);
    ans -= len[pL] - max(0, seg[pL].second - l);

    cout << ans << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
