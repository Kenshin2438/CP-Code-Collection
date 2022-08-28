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

  int l = 0, r = n, ans = -1;
  static const auto chk = [&](int pos) -> bool {
    vector<bool> vis(n + 1, false);
    for (int i = 0; i < pos; i++) vis[a[i]] = true;
    bool ok = true;
    for (int pre = 0, i = pos; i < n; i++) {
      int cur = a[i];
      if (vis[cur]) cur = 0;
      if (cur >= pre) pre = cur;
      else { ok = false; break; }
    }
    return ok;
  };
  while (l <= r) {
    int m = (l + r) >> 1;
    if (chk(m)) r = m - 1, ans = m;
    else l = m + 1;
  }
  vector<int> vis(n + 1, false);
  int res = 0;
  for (int i = 0; i < ans; i++) {
    if (vis[a[i]] == false) res += 1;
    vis[a[i]] = true;
  }
  cout << res << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
