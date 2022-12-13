#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n, m; cin >> n >> m;
  vector<int> h(m), l;
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    for (int j = 0; j < m; j++) {
      if (s[j] == '.') h[j] += 1;
      else h[j] = 0;
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  // cin >> T;
  while (T--) solve();
  return 0;
}