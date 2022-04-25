#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

const int N = (int) 1e6 + 10;

ll sum[N << 2][2], laz[N << 2];

#define ld nd << 1 | 0
#define rd nd << 1 | 1

void merge(int nd) {
  sum[nd][0] = sum[ld][0] + sum[rd][0];
  sum[nd][1] = sum[ld][1] + sum[rd][1];
}

void apply(int s, int t, int nd, ll val) {
  sum[nd][0] += sum[nd][1] * val + (val - 1) * val / 2 * (t - s + 1);
  sum[nd][1] += val * (t - s + 1);
  laz[nd] += val;
}

void push(int s, int t, int nd) {
  int m = (s + t) >> 1;
  apply(s, m, ld, laz[nd]);
  apply(m + 1, t, rd, laz[nd]);
  laz[nd] = 0;
}

void update(int s, int t, int nd, int L, int R, ll val) {
  if (s > R || t < L) return;
  if (s >= L && t <= R) return apply(s, t, nd, val);
  if (laz[nd]) push(s, t, nd);
  int m = (s + t) >> 1;
  update(s, m, ld, L, R, val);
  update(m + 1, t, rd, L, R, val);
  merge(nd);
}

ll query(int s, int t, int nd, int L, int R) {
  if (s > R || t < L) return 0LL;
  if (s >= L && t <= R) return sum[nd][0];
  if (laz[nd]) push(s, t, nd);
  int m = (s + t) >> 1;
  return query(s, m, ld, L, R) + query(m + 1, t, rd, L, R);
}

void SingleTest(int TestCase) {
  int n, q; cin >> n >> q;
  while (q--) {
    int l, r; char op;
    cin >> op >> l >> r;
    if (op == 'U') update(1, n, 1, l, r, 1);
    else cout << query(1, n, 1, l, r) << '\n';
  }
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
