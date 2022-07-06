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

  if (n & 1) {
    cout << -1 << '\n';
  } else {
    int a = 0, b = 0, c = 0;
    for (int i = 31; i >= 0; i--) {
      if (n >> i & 1) {
        a |= (1 << (i - 1));
      }
    }
    cout << a << ' ' << b << ' ' << c << '\n';

    debug((a ^ b) + (b ^ c) + (c ^ a));
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T; cin >> T;
  while (T--) solve();
  return 0;
}