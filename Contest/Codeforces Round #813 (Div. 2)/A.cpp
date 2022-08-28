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
  int n, k; cin >> n >> k;
  vector<int> p(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    int x; cin >> x; p[x] = i;
  }
  int ans = 0;
  for (int i = 1; i <= k; i++) {
    if (p[i] > k) ans += 1;
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
