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

const int N = (int) 1e5 + 10;

ll tr[N << 2], a[N];

#define ld nd << 1 | 0
#define rd nd << 1 | 1

void merge(int nd) {
  tr[nd] = max(tr[ld], tr[rd]);
}
void build(int s, int t, int nd) {
  if (s == t) {
    cin >> a[s];
    tr[nd] = a[s];
    return;
  }
  int m = (s + t) >> 1;
  build(s, m, ld);
  build(m + 1, t, rd);
  merge(nd);
}
int right_most(int s, int t, int nd, int l, int r, ll val) {
  if (s == t) return tr[nd] > val ? s : -1;
  int m = (s + t) >> 1;
  int res = -1;
  if (r >= m + 1 && tr[rd] > val) res = right_most(m + 1, t, rd, l, r, val);
  if (res != -1) return res;
  if (l <= m && tr[ld] > val) res = right_most(s, m, ld, l, r, val);
  return res;
}

void solve() {
  int n, q; cin >> n >> q;
  assert(1 <= n && n <= (int) 1e5);
  assert(1 <= q && q <= (int) 1e5);
  build(1, n, 1);
  for (int _ = 0; _ < q; _++) {
    int pos; ll k;
    cin >> pos >> k;
    assert(1 <= pos && pos <= n);
    assert(0 <= k && k <= (int) 1e9);
    if (pos == 1) {
      cout << -1 << "\n";
    } else {
      cout << right_most(1, n, 1, 1, pos - 1, a[pos] + k) << "\n";
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}