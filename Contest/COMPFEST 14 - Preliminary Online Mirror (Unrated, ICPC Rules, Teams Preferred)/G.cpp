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

void solve() {
  // const int N = 100;
  // vector<ll> sq(N);
  // for (int i = 1; i <= N; i++) {
  //   sq[i - 1] = i * 1LL * i;
  // }
  //
  // set<ll> S;
  // for (int i = 1; i < sz(sq); i++) {
  //   for (int j = 0; j < i; j++) {
  //     S.insert(sq[i] - sq[j]);
  //   }
  // }
  //
  // debug(S);

  int n; cin >> n;
  if (n == 1) return cout << 3 << '\n', void();
  if (n == 2) return cout << 5 << '\n', void();

  n -= 2;
  ll ans = 5 + n / 3 * 4LL;
  if (n % 3 == 0) ans += 0;
  if (n % 3 == 1) ans += 2;
  if (n % 3 == 2) ans += 3;
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
