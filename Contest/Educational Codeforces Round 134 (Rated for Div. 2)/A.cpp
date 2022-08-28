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
  set<char> S;
  {
    string s; cin >> s;
    S.insert(s[0]), S.insert(s[1]);
  }
  {
    string s; cin >> s;
    S.insert(s[0]), S.insert(s[1]);
  }

  int n = sz(S);
  if (n == 1) cout << 0 << '\n';
  else if (n == 2) cout << 1 << '\n';
  else if (n == 3) cout << 2 << '\n';
  else cout << 3 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
