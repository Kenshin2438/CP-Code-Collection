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
  vector<ll> a(n);
  for (ll &x : a) cin >> x;
  partial_sum(all(a), begin(a));

  ll ans = 0;
  for (int i = 0; i < n - 1; i++) {
    ans = max(ans, gcd(a[i], a[n - 1]));
  }
  cout << ans << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}