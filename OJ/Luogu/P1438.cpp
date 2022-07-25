#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) static_cast<int>((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define int long long

struct FenwickTree {
  vector<ll> s, d;

  FenwickTree() = default;
  FenwickTree(int n) : s(n), d(n) {}

  void add(int p, ll dif) {
    ll val = (p + 1) * dif;
    for (; p < sz(s); p |= p + 1) {
      s[p] += val, d[p] += dif;
    }
  }
  ll query(int i) {
    ll S = 0, D = 0;
    for (int p = i; p > 0; p &= p - 1) {
      S += s[p - 1], D += d[p - 1];
    }
    return D * (i + 1) - S;
  }
  void range_add(int l, int r, ll val) {  // [l, r)
    add(l, val), add(r, -val);
  }
};

void solve() {
  int n, m; cin >> n >> m;
  FenwickTree FT(n + 1);
  for (int i = 0, pre = 0; i < n; i++) {
    int x; cin >> x;
    FT.range_add(i, i + 1, x - pre);
    pre = x;
  }
  for (int op; m--; ) {
    cin >> op;
    if (op == 1) {
      int l, r, k, d;
      cin >> l >> r >> k >> d;
      FT.range_add(l - 1, l, k);
      FT.range_add(l, r, d);
      FT.range_add(r, r + 1, -(k + (r - l) * 1LL * d));
    } else {
      int p; cin >> p;
      cout << FT.query(p) << '\n';
    }
  }
}

signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
