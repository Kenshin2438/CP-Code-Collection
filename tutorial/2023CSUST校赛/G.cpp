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
  int n, m; cin >> n >> m;
  assert(1 <= n && n <= (int) 2E5);
  assert(1 <= m && m <= (int) 1E9);

  map<int, int> Mp;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    assert(0 <= x && x <= (int) 1E9);
    x %= m;

    if (x == 0) {
      if (Mp.find(0) != end(Mp)) ans += Mp[0];
    } else {
      if (Mp.find(x) != end(Mp)) ans += Mp[x];
      if (m - x != x && Mp.find(m - x) != end(Mp)) 
        ans += Mp[m - x];
    }
    Mp[x] += 1;
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}