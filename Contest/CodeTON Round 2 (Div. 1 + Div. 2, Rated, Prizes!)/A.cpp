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
  int n, m; cin >> n >> m;
  string a, b; cin >> a >> b;
  bool ans = true;
  if (n == m) {
    ans = (a == b);
  } else {
    ans = (a.substr(n - m + 1) == b.substr(1) && count(a.begin(), a.begin() + n - m + 1, b.front()));
  }
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
