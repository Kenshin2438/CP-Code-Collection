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
  int n; cin >> n;
  vector<int> bit(16, 0);
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    for (int b = 0; b <= 15; b++) {
      bit[b] += (x >> b & 1);
    }
  }
  debug(bit);
  ll S = 0, SS = 0;
  for (int i = 1; i <= n; i++) {
    ll x = 0;
    for (int b = 0; b <= 15; b++) {
      if (bit[b]) {
        bit[b] -= 1;
        x |= 1 << b;
      }
    }
    S += x, SS += x * 1LL * x;
  }
  ll U = n * SS - S * S;
  ll D = n * 1LL * n;
  ll g = __gcd(U, D);
  cout << U/g << "/" << D/g << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
