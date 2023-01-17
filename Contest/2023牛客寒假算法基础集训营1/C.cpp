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
  vector<int> a;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (x != 0) a.emplace_back(x);
  }
  sort(all(a), greater<int>());
  debug(a);
  int ans = 0, cnt = 0;
  for (int i = 0; i < sz(a); i++) {
    if (a[i] >= cnt + 1) {
      cnt += 1;
    } else {
      ans += cnt;
      cnt = 1;
    }
  }
  ans += cnt;
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}