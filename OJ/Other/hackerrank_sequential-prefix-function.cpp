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
  vector<int> s, lps, pre;

  int q; cin >> q;
  while (q--) {
    char op; cin >> op;
    if (op == '-') {
      s.pop_back(), lps.pop_back(), pre.pop_back();
    } else {
      int x; cin >> x;
      s.push_back(x);

      int g =
    }
    cout << max(0, lps.back()) << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
