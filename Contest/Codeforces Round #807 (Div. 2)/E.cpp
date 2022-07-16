#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int M = 2e5 + 100, N = M + 10;
int cnt[N], n, a[N], q;

#define ld (nd << 1 | 0)
#define rd (nd << 1 | 1)
int sum[N << 2], laz[N << 2];
void merge(int nd) { sum[nd] = sum[ld] + sum[rd]; }
void build(int s, int t, int nd) {
  sum[nd] = laz[nd] = 0;
  if (s == t) return sum[nd] = cnt[s], void();
  int m = (s + t) >> 1;
  build(s, m, ld), build(m + 1, t, rd), merge(nd);
}
void push_lazy(int s, int t, int nd, int v) {
  sum[nd] += v * (t - s + 1);
  laz[nd] += v;
}
void down_lazy(int s, int t, int nd) {
  if (laz[nd] == 0) return;
  int m = (s + t) >> 1;
  push_lazy(s, m, ld, laz[nd]);
  push_lazy(m + 1, t, rd, laz[nd]);
  laz[nd] = 0;
}
void update(int s, int t, int nd, int l, int r, int v) {
  if (l > t || r < s) return;
  if (l <= s && t <= r) return push_lazy(s, t, nd, v);
  down_lazy(s, t, nd);
  int m = (s + t) >> 1;
  update(s, m, ld, l, r, v);
  update(m + 1, t, rd, l, r, v);
  merge(nd);
}
int get(int s, int t, int nd, int p) {
  if (s == t) return sum[nd];
  down_lazy(s, t, nd);
  int m = (s + t) >> 1;
  if (p <= m) return get(s, m, ld, p);
  else return get(m + 1, t, rd, p);
}
int query(int s, int t, int nd) {
  if (s == t) return s;
  down_lazy(s, t, nd);
  int m = (s + t) >> 1;
  if (sum[rd]) return query(m + 1, t, rd);
  else return query(s, m, ld);
}
int S(int s, int t, int nd, int l, int r) {
  if (l > t || r < s) return 0;
  if (l <= s && t <= r) return sum[nd];
  down_lazy(s, t, nd);
  int m = (s + t) >> 1;
  return S(s, m, ld, l, r) + S(m + 1, t, rd, l, r);
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    cnt[ a[i] ] += 1;
  }
  for (int i = 1; i + 1 < N; i++) {
    cnt[i + 1] += cnt[i] / 2, cnt[i] %= 2;
  }
  build(1, M, 1);
  while (q--) {
    int p, v; cin >> p >> v;
    {
      int op = get(1, M, 1, a[p]);
      if (op == 1) {
        update(1, M, 1, a[p], a[p], -1);
      } else {
        int lim = a[p], l = a[p], r = M;
        while (l <= r) {
          int m = (l + r) >> 1;
          if (S(1, M, 1, a[p], m) == 0) {
            lim = m, l = m + 1;
          } else {
            r = m - 1;
          }
        }
        update(1, M, 1, lim + 1, lim + 1, -1);
        update(1, M, 1, a[p], lim, 1);
      }
    }
    a[p] = v;
    {
      int op = get(1, M, 1, a[p]);
      if (op == 1) {
        int lim = a[p], l = a[p], r = M;
        while (l <= r) {
          int m = (l + r) >> 1;
          if (S(1, M, 1, a[p], m) == (m - a[p] + 1)) {
            lim = m, l = m + 1;
          } else {
            r = m - 1;
          }
        }
        update(1, M, 1, lim + 1, lim + 1, 1);
        update(1, M, 1, a[p], lim, -1);
      } else {
        update(1, M, 1, a[p], a[p], 1);
      }
    }
    cout << query(1, M, 1) << '\n';
  }
  return 0;
}