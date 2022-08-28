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
  vector<int> a(n);
  for (int &x : a) cin >> x;

  int ans = n, pre = 0;
  set<int> S; S.insert(0);
  for (int i = 0; i < n; i++) {
    if (i == 0) pre = a[i];
    else pre ^= a[i];

    // debug(S, pre);

    if (S.count(pre)) ans -= 1, S.clear();
    S.insert(pre);
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
