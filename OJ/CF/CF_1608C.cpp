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
  vector<int> a(n), b(n);
  for (int &x : a) cin >> x;
  for (int &x : b) cin >> x;
  set<pair<int, int>> A, B;
  for (int i = 0; i < n; i++) {
    A.insert({a[i], i});
    B.insert({b[i], i});
  }
  int maxA = A.rbegin()->first;
  int maxB = B.rbegin()->first;
  string ans(n, '0');
  while (not A.empty()) {
    if (A.rbegin()->first >= maxA) {
      int p = A.rbegin()->second;
      ans[p] = '1';
      A.erase({a[p], p});
      B.erase({b[p], p});
      maxA = min(maxA, a[p]);
      maxB = min(maxB, b[p]);
      continue;
    }
    if (B.rbegin()->first >= maxB) {
      int p = B.rbegin()->second;
      ans[p] = '1';
      A.erase({a[p], p});
      B.erase({b[p], p});
      maxA = min(maxA, a[p]);
      maxB = min(maxB, b[p]);
      continue;
    }
    break;
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
