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
  int n; cin >> n;
  vector<vector<int>> r(n);
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    --x;
    r[x].push_back(i);
  }
  for (int i = 0; i < n; i++) {
    if (r[i].empty()) cout << 0 << ' ';
    else {
      vector<int> o(2, 0);
      for (int x : r[i]) {
        int v = o[(x % 2) ^ 0 ^ 1] + 1;
        o[x % 2] = max(o[x % 2], v);
      }
      cout << max(o[0], o[1]) << ' ';
    }
  }
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve(); 
 
  return 0;
}