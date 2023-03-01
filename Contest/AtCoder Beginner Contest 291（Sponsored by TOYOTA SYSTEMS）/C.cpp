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
  int n; cin >> n;
  string s; cin >> s;
  
  int x = 0, y = 0;
  set<pair<int, int>> S;
  S.emplace(x, y);
  for (int i = 0; i < n; i++) {
    if (s[i] == 'R') x += 1;
    if (s[i] == 'L') x -= 1;
    if (s[i] == 'U') y += 1;
    if (s[i] == 'D') y -= 1;
    S.emplace(x, y);
  }
  if (sz(S) == n + 1) {
    cout << "No";
  } else {
    cout << "Yes";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}