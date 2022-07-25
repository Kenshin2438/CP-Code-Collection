#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int N = 1e5 + 10;
#define ld nd << 1 | 0
#define rd nd << 1 | 1

int n, q;
char str[N];
int sum[N << 2], laz[N << 2], mi[N << 2], mx[N << 2];
void merge(int nd) {
  sum[nd] = sum[ld] + sum[rd];
  mi[nd] = min(sum[ld] + mi[rd], mi[ld]);
  mx[nd] = max(sum[ld] + mx[rd], mx[ld]);
}
void build(int s, int t, int nd) {
  laz[nd] = 1;
  if (s == t) {
    sum[nd] = (str[t] == '(' ? 1 : -1);
    mi[nd] = mx[nd] = sum[nd];
    return;
  }
  int m = (s + t) >> 1;
  build(s, m, ld), build(m + 1, t, rd), merge(nd);
}
void pushlz(int nd, int v) {
  laz[nd] *= v;
  sum[nd] *= v;
  swap(mi[nd], mx[nd]);
  mi[nd] *= v;
  mx[nd] *= v;
}
void downlz(int nd) {
  if (laz[nd] == 1) return;
  pushlz(ld, laz[nd]);
  pushlz(rd, laz[nd]);
  laz[nd] = 1;
}
void update(int s, int t, int nd, int l, int r, int v) {
  if (l <= s && t <= r) return pushlz(nd, v);
  downlz(nd);
  int m = (s + t) >> 1;
  if (l <= m) update(s, m, ld, l, r, v);
  if (r > m) update(m + 1, t, rd, l, r, v);
  merge(nd);
}

void solve() {
  cin >> n >> q >> (str + 1);
  build(1, n, 1);
  for (int l, r; q--; ) {
    cin >> l >> r;
    update(1, n, 1, l, r, -1);
    int S = sum[1], M = mi[1];
    cout << ((S == 0 && M == 0) ? "YES" : "NO") << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
