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
  int n; cin >> n;
  vector<int> a(n), b(n);
  for (int &x : a) cin >> x;
  for (int &x : b) cin >> x;

  int z1 = 0, z0 = 0;
  for (int i = 0; i < n; i++) {
    z1 += a[i] != b[i] && a[i] == 1;
    z0 += a[i] != b[i] && a[i] == 0;
  }

  if (z1 == 0 && z0 == 0) {
    cout << 0 << '\n';
  } else {
    if (z1 == z0) cout << 1 << '\n';
    else cout << min(z1 + z0, abs(z1 - z0) + 1) << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
