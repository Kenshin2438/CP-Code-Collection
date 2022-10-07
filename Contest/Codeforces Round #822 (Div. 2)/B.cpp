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
  for (int i = 1; i <= n; i++) {
    vector<int> p(i, 0);
    p[0] = p[i - 1] = 1;
    for (int j = 0; j < i; j++) {
      cout << p[j] << " \n"[j + 1 == i];
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
