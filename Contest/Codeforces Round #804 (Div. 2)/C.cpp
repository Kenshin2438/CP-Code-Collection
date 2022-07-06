#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int mod = 1e9 + 7;

ll fac[100005];

void solve() {
  int n; cin >> n;
  vector<int> p(n);
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    p[x] = i;
  }

  int l = 1e9, r = -1e9;
  ll ans = 1;
  for (int i = 0; i < n; i++) {
    l = min(l, p[i]);
    r = max(r, p[i]);
    if (i + 1 < n) {
      if (p[i + 1] < l || p[i + 1] > r) {
        continue;
      } else {
        ans = ans * (r - l - i) % mod;
      }
    }
  }
  cout << ans << '\n'; 
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  fac[0] = 1;
  for (int i = 1; i <= 1e5; i++) {
    fac[i] = fac[i - 1] * i % mod;
  }

  int T; cin >> T;
  while (T--) solve();
  return 0;
}