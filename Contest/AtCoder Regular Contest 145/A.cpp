#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

/**
4
ABAA
**/

void solve() {
  int n; cin >> n;
  string s; cin >> s;

  int l = 0, r = n - 1;
  bool ans = true;
  while (l < r) {
    if (s[l] == s[r]) l++, r--;
    else {
      debug(l, r);
      if (s[r] == 'A') {
        if (l + 1 < r) {
          s[l + 1] = 'B', s[l] = 'A';
          l++, r--;
        } else if (l + 1 == r && l - 1 >= 0 && s[l - 1] == 'A') {
          s[l] = s[r] = 'B';
          l++, r--;
        } else {
          ans = false;
          break;
        }
      } else { // s[r] == 'B'
        if (l - 1 >= 0) {
          if (s[l - 1] == 'A') s[l] = 'B';
          else s[r] = 'A';
          l++, r--;
        } else {
          ans = false;
          break;
        }
      }
    }
  }
  cout << (ans ? "Yes" : "No") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
