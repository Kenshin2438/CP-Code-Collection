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
  ll a, b; cin >> a >> b;
  ll n, m; cin >> n >> m;

  ll n0 = n / (m + 1), n1 = n % (m + 1);

  ll ans = min(
    n0 * m * a + n1 * min(a, b),
    n * b
  );
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}