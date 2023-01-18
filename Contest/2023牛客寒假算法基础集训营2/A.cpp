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

void solve() {
  int n; cin >> n;
  int l1, r1; cin >> l1 >> r1;
  int l2, r2; cin >> l2 >> r2;

  int ans = 0;
  for (int a = l1; a <= r1; a++) {
    int t = n - a;
    ans += t >= l2 && t <= r2;
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