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
  vector<int> a(n);
  for (int &x : a) cin >> x;

  int l = 1;
  while (l < n && a[l] >= a[l - 1]) l += 1;

  bool ok = true;
  for (int i = l; i < n; i++) {
    if (a[i] > a[i - 1]) ok = false;
  }

  if (ok) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
