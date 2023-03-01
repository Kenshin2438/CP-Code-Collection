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
  int n, m, d; cin >> n >> m >> d;
  vector<int> a(m), pos(n);
  for (int i = 0; i < n; i++) {
    int x; cin >> x; x--;
    pos[x] = i;
  }
  for (int &x : a) cin >> x, --x;
  int ans = INT_MAX;
  for (int i = 0; i + 1 < m; i++) {
    if (pos[a[i]] < pos[a[i + 1]] && pos[a[i + 1]] <= pos[a[i]] + d) {
      ans = min(ans, pos[a[i + 1]] - pos[a[i]]);
      if (d + 2 <= n) ans = min(ans, d + 1 - (pos[a[i + 1]] - pos[a[i]]));
    } else {
      ans = 0;
    }
  }
  cout << (ans == INT_MAX ? 0 : ans) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}