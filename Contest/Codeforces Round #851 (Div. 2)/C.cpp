#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  int n; cin >> n;
  if (n % 2 == 0) {
    return cout << "NO\n", void();
  }

  vector<int> a;
  for (int i = 1; i <= n; i+=2) {
    a.emplace_back(i);
  }
  for (int i = 2; i <= n; i+=2) {
    a.emplace_back(i);
  }
  debug(a);
  int B = (n + 1) / 2 * 3;
  debug(B);
  cout << "YES\n";
  for (int i = 0; i < n; i++) {
    cout << a[i] << " " << B - a[i] << "\n";
    B += 1;
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}