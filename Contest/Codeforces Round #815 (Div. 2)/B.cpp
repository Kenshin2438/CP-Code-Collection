#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

/**

[p]: {0, 1, 2, 3}
[p]: {0, 1, 3, 2}
[p]: {0, 2, 1, 3}
[p]: {0, 2, 3, 1}
[p]: {0, 3, 1, 2}
[p]: {0, 3, 2, 1}
[p]: {1, 0, 2, 3}
[p]: {1, 0, 3, 2}
[p]: {1, 2, 0, 3}
[p]: {1, 2, 3, 0}
[p]: {1, 3, 0, 2}
[p]: {1, 3, 2, 0}
[p]: {2, 0, 1, 3}
[p]: {2, 0, 3, 1}
[p]: {2, 1, 0, 3}
[p]: {2, 1, 3, 0}
[p]: {2, 3, 0, 1}
[p]: {2, 3, 1, 0}
[p]: {3, 0, 1, 2}
[p]: {3, 0, 2, 1}
[p]: {3, 1, 0, 2}
[p]: {3, 1, 2, 0}
[p]: {3, 2, 0, 1}
[p]: {3, 2, 1, 0}

**/

void solve() {
  int n; cin >> n;
  vector<ll> a(n);
  for (auto &&x : a) cin >> x;

  sort(all(a));
  cout << (a[n - 1] + a[n - 2] - a[0] - a[1]) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
