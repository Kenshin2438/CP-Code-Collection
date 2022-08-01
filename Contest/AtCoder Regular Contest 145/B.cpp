#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

/**

5 6 5

**/

void solve() {
  ll n, a, b; cin >> n >> a >> b;
  if (a <= b) cout << max(0LL, n - a + 1) << '\n';
  else {
    cout << max(0LL, n / a - 1) * b + (n >= a) + (n > a) * min(n % a, b - 1) << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
