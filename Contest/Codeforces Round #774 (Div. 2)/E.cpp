#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

bitset<20000005> S;
void solve() {
  int n, m; cin >> n >> m;
  vector<ll> val(25, 0);
  for (int i = 1; i <= 20; i++) {
    for (int j = 1; j <= m; j++) S[i * j] = 1;
    val[i] = S.count();
  }
  ll ans = 1;
  vector<bool> vis(n + 1, false);
  for (int i = 2; i <= n; i++) {
    if (vis[i]) continue;
    ll e = 1, cur = i;
    while (cur <= n) {
      vis[cur] = true;
      cur *= i, e += 1;
    }
    ans += val[e - 1];
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
