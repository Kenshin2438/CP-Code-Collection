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
  vector<int> a(n);
  for (int &x : a) cin >> x;

  int zero = count(all(a), 0);
  int mx = *max_element(all(a));
  int ans = -1;

  if (n - zero >= zero - 1) {
    ans = 0;
  } else {
    ans = 1 + (mx == 1);
  }

  cout << ans << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}