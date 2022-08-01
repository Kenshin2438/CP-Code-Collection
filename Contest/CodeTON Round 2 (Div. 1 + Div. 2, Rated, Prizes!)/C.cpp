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
  vector<int> a(m);
  for (auto &&x : a) cin >> x;
  sort(all(a));

  if (m == 1) return cout << "2\n", void();
  vector<ll> L;
  // length, edge
  for (int i = 0; i + 1 < m; i++) {
    ll len = a[i + 1] - a[i] - 1;
    if (len == 0) continue;
    L.emplace_back(len);
  }
  if (n - a.back() + a.front() - 1 > 0) {
    ll len = n - a.back() + a.front() - 1;
    L.emplace_back(len);
  }
  sort(all(L), greater<ll>());
  // debug(L);
  ll t = 0, ans = n;
  for (const ll &len : L) {
    ll T = (len - t * 2);
    if (T > 0) {
      if (T <= 2) {
        ans -= 1, t += 1;
      } else {
        ans -= T - 1, t += 2;
      }
    }
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
