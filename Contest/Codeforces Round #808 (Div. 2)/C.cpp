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

  if (q >= n) {
    while (n--) cout << 1;
  } else {
    for (int &x : a) if (x > q) x = q + 1;
    vector<int> ans(n, 0);
    int now = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (now >= a[i]) {
        ans[i] = 1;
      } else {
        if (now != q) now += 1, ans[i] = 1;
      }
    }
    for (int x : ans) cout << x;
  }
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}