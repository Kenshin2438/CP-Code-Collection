#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n, c, q; cin >> n >> c >> q;
  string s; cin >> s;
  vector<pair<ll, ll>> seg, ops(c);
  seg.emplace_back(0LL, n - 1LL);
  ll len = n;
  for (auto &&[l, r] : ops) {
    cin >> l >> r;
    --l, --r;
    seg.emplace_back(len, len + (r - l + 1) - 1);
    len += (r - l + 1);
  }

  while (q--) {
    ll pos; cin >> pos;
    --pos;

    while (pos >= n) {
      for (int i = c; i >= 1; i--) {
        auto [pl, pr] = seg[i];
        if (pos >= pl && pos <= pr) {
          auto [l, r] = ops[i - 1];
          pos = l + (pos - pl + 1) - 1;
        }
      }
    }
    cout << s[pos] << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}