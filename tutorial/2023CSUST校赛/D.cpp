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
  assert(1 <= n && n <= (int) 5E5);
  ll D = n * 1LL * (n - 1) / 2;
  ll U = 0LL;

  array<int, 210> pre {};
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    assert(150 <= x && x <= 205);
    U += pre[x];

    for (int j = 150; j < x; j++) {
      pre[j] += 1;
    }
  }

  debug(D, U);

  ll g = __gcd(D, U);
  cout << U / g << '/' << D / g << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}