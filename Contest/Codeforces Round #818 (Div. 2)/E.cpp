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

const int mod = 1e9 + 7;

void solve() {
  int n; cin >> n;

  vector<int> phi(n + 1);
  {
    vector<int> p;
    vector<bool> ntp(n + 1, false);

    phi[1] = 0;
    for (int i = 2; i <= n; i++) {
      if (ntp[i] == false) p.emplace_back(i), phi[i] = i - 1;
      for (const int &pr : p) {
        if (pr * 1LL * i > n) break;
        ntp[pr * i] = true;
        if (i % pr == 0) {
          phi[pr * i] = phi[i] * pr;
          break;
        } else {
          phi[pr * i] = phi[i] * (pr - 1);
        }
      }
    }
  }

  // debug(phi);

  ll ans = 0;
  for (int c = 1; c <= n - 2; c++) {
    int m = (n - c);

    ll SUM = 0;
    for (int g = 1; g * 1LL * g <= m; g++) if (m % g == 0) {
      int k = m / g;
      SUM = (SUM + g / __gcd(g, c) * phi[k] % mod) % mod;
      if (k == g) break;
      SUM = (SUM + k / __gcd(k, c) * phi[g] % mod) % mod;
    }
    ans = (ans + SUM * c % mod) % mod;
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
