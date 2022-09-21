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
  int n, m; cin >> n >> m;

  ll p, x, a, b, c;
  cin >> p >> x >> a >> b >> c;

  unordered_map<ll, int> pos;
  int ans = 0;
  for (int i = 1; i <= n + m; i++) {
    ll y = (a * x % p * x + b * x % p + c) % p;
    debug(y);
    if (pos.count(y) == 0) pos[y] = i;
    else if (i > n) {
      ans = max(ans, min(n - pos[y] + 1, n + m - i + 1));
    }
    swap(x, y);
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
