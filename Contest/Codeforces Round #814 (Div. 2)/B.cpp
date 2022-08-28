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
  int n, k; cin >> n >> k;
  if (k & 1) {
    cout << "YES\n";
    for (int i = 1; i + 1 <= n; i += 2) {
      cout << i << " " << i + 1 << '\n';
    }
  } else {
    if (k >> 1 & 1) {
      cout << "YES\n";
      for (int i = 1; i + 1 <= n; i += 2) {
        if (i % 4 == 1) cout << i + 1 << ' ' << i << '\n';
        else cout << i << ' ' << i + 1 << '\n';
      }
    } else {
      cout << "NO\n";
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
