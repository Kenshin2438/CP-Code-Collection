#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m; cin >> n >> m;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  const int S = sqrt(n) + 1;
  vector<int> b(n), l(n / S + 1, n), r(n / S + 1, -1);
  for (int i = 0; i < n; i++) {
    b[i] = i / S;
    l[ b[i] ] = min(l[ b[i] ], i);
    r[ b[i] ] = max(r[ b[i] ], i);
  }
  vector<array<int, 3>> info(n);
  for (int i = 0; i <= b[n - 1]; i++) {
    for (int j = r[i]; j >= l[i]; j--) {
      if (j + a[j] > r[i]) {
        info[j] = { 1, j + a[j], j };
      } else {
        auto [p, q, w] = info[j + a[j]];
        info[j] = { 1 + p, q, w };
      }
    }
  }
  while (m--) {
    int op; cin >> op;
    if (op == 0) {
      int x, y; cin >> x >> y;
      --x;
      a[x] = y;
      for (int j = x; j >= l[ b[x] ]; j--) {
        if (j + a[j] > r[ b[x] ]) {
          info[j] = { 1, j + a[j], j };
        } else {
          auto [p, q, w] = info[j + a[j]];
          info[j] = { 1 + p, q, w };
        }
      }
    } else {
      int now; cin >> now;
      --now;
      int num = 0, pos;
      while (true) {
        auto [p, q, w] = info[now];
        num += p;
        pos = w;
        if (q >= n) {
          break;
        } else {
          now = q;
        }
      }
      cout << pos + 1 << ' ' << num << '\n';
    }
  }
  return 0;
}
