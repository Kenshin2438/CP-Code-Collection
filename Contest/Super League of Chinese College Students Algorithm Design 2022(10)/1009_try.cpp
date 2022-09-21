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
  string s; cin >> s;

  int num = 2 * (n - 1) + (s[0] == 'A' ? 1 : 2);
  if (num <= 5) cout << 1 << '\n';
  else if (num <= 9) cout << 2 << '\n';
  else {
    num -= 9;
    int ans = 2 + num / 14 * 3;
    num %= 14;
    if (1 <= num && num <= 5) ans += 1;
    else if (6 <= num && num <= 10) ans += 2;
    else if (11 <= num && num <= 13) ans += 3;
    cout << ans << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
