#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

ll calc(ll LIM, ll n) {
  for (ll x = 2; x * x <= n; x++) {
    if (n % x == 0) {
      if (x > LIM) return x;
      while (n % x == 0) n /= x;
    }
  }
  if (n != 1 && n > LIM) return n;
  return -1;
}

void solve() {
  ll P, Q, E; cin >> P >> Q >> E;
  ll M = calc(max({P, Q, E}), P * Q - 1);
  if (M == -1) return cout << "shuanQ\n", void();
  cout << E * Q % M << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
