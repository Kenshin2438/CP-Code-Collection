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
  string s; cin >> s;
  int a = 0, b = 0;
  int r = 5, t = 5;
  for (int i = 0; i < 10; i++) {
    int soc = s[i] - '0';
    if (i & 1) {
      a += soc;
      r -= 1;
    } else {
      b += soc;
      t -= 1;
    }
    if (a + r < b || b + t < a) {
      return cout << i + 1 << '\n', void();
    }
  }
  cout << -1 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}