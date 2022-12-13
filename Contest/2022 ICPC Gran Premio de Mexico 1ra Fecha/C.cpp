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

const int N = 5e5 + 10;
struct segmentTree {
  ll seg[N << 2], laz[N << 2];
  #define ld nd << 1 | 0
  #define rd nd << 1 | 1
  void merge(int nd) {
    seg[nd] = seg[ld] + seg[rd];
  }
  void clean() {
    memset(seg, 0, sizeof seg);
    memset(laz, 0, sizeof laz);
  }
  void pushlz(int s, int t, int nd, ll val) {
    seg[nd] += val * (t - s + 1);
    laz[nd] += val;
  }
  void downlz(int s, int t, int nd) {
    if (laz[nd] == 0) return;
    int m = (s + t) >> 1;
    pushlz(s, m, ld, laz[nd]);
    pushlz(m + 1, t, rd, laz[nd]);
    laz[nd] = 0;
  }
  void add(int s, int t, int nd, int l, int r, ll val) {
    if (l <= s && t <= r) return pushlz(s, t, nd, val);
    downlz(s, t, nd);
    int m = (s + t) >> 1;
    if (l <= m) add(s, m, ld, l, r, val);
    if (r > m) add(m + 1, t, rd, l, r, val);
    merge(nd);
  }
  int leftmost(int s, int t, int nd, ll val) {
    if (s == t) return s;
    downlz(s, t, nd);
    int m = (s + t) >> 1;
    if (seg[ld] >= val) return leftmost(s, m, ld, val);
    return leftmost(m + 1, t, rd, val - seg[ld]);
  }
} tr;

void solve() {
  int n, q; cin >> n >> q;
  vector<ll> a(n);
  for (ll &x : a) cin >> x;

  while (q--) {
    int siz; cin >> siz;
    vector<array<int, 3>> ops(siz);
    for (auto &&[l, r, x] : ops) cin >> l >> r >> x;
    ll N = 0;

    for (const auto &[l, r, x] : ops) {
      N += x * 1LL * (r - l + 1);
      tr.add(1, n, 1, l, r, x);
    }
    int poslower = tr.leftmost(1, n, 1, N / 2);
		int posupper = tr.leftmost(1, n, 1, N / 2 + 1);
    if (poslower + 1 == posupper && N % 2 == 0) {
      ll A = (a[poslower - 1] + a[posupper - 1]) / 2;
      ll B = (a[poslower - 1] + a[posupper - 1]) % 2;
      cout << A << "." << (B ? 5 : 0) << '\n';
    } else {
      cout << a[posupper - 1] << '\n';
    }
    for (const auto &[l, r, x] : ops) tr.add(1, n, 1, l, r, -x);
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
