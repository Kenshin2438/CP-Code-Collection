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

  vector<int> lim = b;
  for (int i = 0; i < n; i++) {
    if (a[i] > b[i]) {
    return cout << "NO\n", void();
    } else if (a[i] == b[i]) {
      lim[i] = max(lim[i], a[i]);
    } else {
      int j = (i + 1) % n;
      lim[j] = max(lim[j], b[i] - 1);
    }
  }
  // debug(lim);

  if (lim != b) cout << "NO\n";
  else cout << "YES\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
