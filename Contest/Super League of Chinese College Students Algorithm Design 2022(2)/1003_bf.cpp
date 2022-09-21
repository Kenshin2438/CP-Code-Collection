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
  int ans = 0;
  while (q--) {
    int op; cin >> op;
    if (op == 1) {
      int l, r; cin >> l >> r;
      --l, --r;
      for (int i = n - 1; i - (r - l + 1) > r; i--) {
        a[i] = a[i - (r - l + 1)];
      }
      for (int i = 0; i < (r - l + 1); i++) {
        if (r + 1 + i >= n) break;
        a[r + 1 + i] = a[l + i];
      }
    } else {
      int p; cin >> p;
      --p;
      ans ^= a[p];
    }
    debug(a);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
