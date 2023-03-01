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
  ll L, R; cin >> L >> R;
  ll ans = 0;

  ans += max(0LL, R / 2 - L + 1);

  L = L - 1;
  for (ll bl = 1, br; bl <= L; bl = br + 1) {
    br = min(L, L / (L / bl));
    ll k = (L / bl) + 1 + 1;
    ll lim = R / k;
    ans += max(0LL, min(lim, br) - bl + 1);
  }
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