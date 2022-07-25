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
  vector<int> a(3);
  for (int &x : a) cin >> x;
  if (a[n - 1] != 0 && a[ a[n - 1] - 1] != 0) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
