#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n, q; cin >> n >> q;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  vector<vector<int>> Q(q);
  for (auto &v : Q) {
    int op; cin >> op;
    if (op == 1) {
      int l, r; cin >> l >> r;
      v = {op, l - 1, r};
    } else {
      int p; cin >> p;
      v = {op, p - 1};
    }
  }
  const int N = 1e5;
  bitset<N> B;
  for (int i = q - 1; i >= 0; i--) {
    int op = Q[i][0];
    if (op == 2) {
      int p = Q[i][1];
      B.flip(p);
    } else {
      int l = Q[i][1], r = Q[i][2];
      B = (B >> r << r >> (r - l)) ^ (B << (N - r) >> (N - r));
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++) if (B[i]) ans ^= a[i];
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
