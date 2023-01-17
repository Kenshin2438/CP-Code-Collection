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

#define ld nd << 1 | 0
#define rd nd << 1 | 1

const int N = 1e6 + 10;

long long tr[N];
bool ok[N];

void merge(int nd) {
  tr[nd] = tr[ld] + tr[rd];
  ok[nd] = ok[ld] && ok[rd];
}

void build(int s, int t, int nd) {
  if (s == t) {
    cin >> tr[nd];
    ok[nd] = (
      tr[nd] == 0 || tr[nd] == 99 || tr[nd] == 100
    );
    return;
  }
  int mid = (s + t) >> 1;
  build(s, mid, ld);
  build(mid + 1, t, rd);
  merge(nd);
}

inline long long f(long long x) { 
  return round(10 * sqrt(x)); 
}

void modify(int s, int t, int nd, int l, int r, int k) {
  if (ok[nd]) return;
  if (s == t) {
    for (int _ = 0; _ < k; _++) {
      tr[nd] = f(tr[nd]);
      ok[nd] = (
        tr[nd] == 0 || tr[nd] == 99 || tr[nd] == 100
      );
      if (ok[nd]) break;
    }
    return;
  }
  int mid = (s + t) >> 1;
  if (mid >= l) modify(s, mid, ld, l, r, k);
  if (mid + 1 <= r) modify(mid + 1, t, rd, l, r, k);
  merge(nd);
}

void solve() {
  int n, m; cin >> n >> m;
  build(1, n, 1);
  for (int op, l, r, k; m--;) {
    cin >> op;
    if (op == 1) {
      cin >> l >> r >> k;
      modify(1, n, 1, l, r, k);
    } else {
      cout << tr[1] << '\n';
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}