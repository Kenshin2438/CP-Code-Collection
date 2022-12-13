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

  int Q = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'Q') {
      Q += 1;
    } else {
      Q = max(0, Q - 1);
    }
  }
  cout << (Q == 0 ? "Yes" : "No") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
