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
  string s; cin >> s;
  int l = count(all(s), '(');
  int r = count(all(s), ')');
  int n = s.length();

  if (l == n / 2 || r == n / 2) return cout << "YES\n", void();
  int pl = -1, pr = -1;
  for (int i = 0; i < n; i++) {
    if (s[i] == '?') {
      if (l != n / 2) {
        l += 1, s[i] = '(';
        pl = i;
      } else {
        r += 1, s[i] = ')';
        if (pr == -1) pr = i;
      }
    }
  }
  swap(s[pl], s[pr]);
  auto check = [&](const string &s) -> bool {
    int x = 0;
    for (const char &c : s) {
      if (c == ')') x -= 1;
      else x += 1;

      if (x < 0) return false;
    }
    return x == 0;
  };
  cout << (check(s) ? "NO" : "YES") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
