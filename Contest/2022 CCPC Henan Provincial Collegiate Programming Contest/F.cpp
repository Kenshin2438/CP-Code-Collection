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
  if (n == 2 || n == 4) return cout << "-1\n", void();
  if (n & 1) {
    int m = n / 2, st = 0;
    cout << m + 1 << '\n';
    for (int x = 0; x <= m; x++) {
      cout << st + x << " \n"[x == m];
    }
  } else {
    int m = n / 2 - 1, st = 5;
    cout << m + 1 << '\n';
    for (int x = 0; x < m; x++) {
      cout << st + x << " ";
    }
    cout << st - 2 << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
