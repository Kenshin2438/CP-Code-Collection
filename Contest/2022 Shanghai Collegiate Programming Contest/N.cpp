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
  string a, b; cin >> a >> b;
  if (a == b) {
    cout << a << "=" << b << '\n';
  } else if (a > b) {
    cout << a << ">" << b << '\n';
  } else {
    cout << a << "<" << b << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
