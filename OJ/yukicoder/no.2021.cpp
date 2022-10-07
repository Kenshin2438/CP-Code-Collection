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

  int ans = 0;
  bool BB = false;
  for (int i = 1; i < n; i++) {
    ans += s[i] == 'A' || s[i - 1] == 'A';
    BB |= s[i] == 'B' && s[i - 1] == 'B';
  }
  for (int i = 1; i + 1 < n; i++) {
    ans -= s[i - 1] == 'B' && s[i] == 'A' && s[i + 1] == 'B';
  }
  cout << (ans + BB) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
