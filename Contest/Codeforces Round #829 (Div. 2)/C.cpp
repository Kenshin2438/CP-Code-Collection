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

  if ((n - count(all(a), 0)) & 1) return cout << "-1\n", void();

  int c1 = count(all(a), 1);
  int c0 = count(all(a), -1);
  if (c1 == c0) {
    cout << n << '\n';
    for (int i = 1; i <= n; i++) {
      cout << i << ' ' << i << '\n';
    }
  } else if (c1 > c0) {
    vector<pair<int, int>> ans;
    int o = (c1 - c0) / 2;
    for (int i = 0; i < n; i++) {
      if (i + 1 < n && o && ((a[i] == 0 && a[i + 1] == 1) || (a[i] == 1 && a[i + 1] == 1))) {
        ans.emplace_back(i, i + 1);
        i++, o--;
      } else {
        ans.emplace_back(i, i);
      }
    }
    cout << sz(ans) << '\n';
    for (const auto &[l, r] : ans) {
      cout << l + 1 << ' ' << r + 1 << '\n';
    }
  } else {
    vector<pair<int, int>> ans;
    int o = (c0 - c1) / 2;
    for (int i = 0; i < n; i++) {
      if (i + 1 < n && o && ((a[i] == 0 && a[i + 1] == -1) || (a[i] == -1 && a[i + 1] == -1))) {
        ans.emplace_back(i, i + 1);
        i++, o--;
      } else {
        ans.emplace_back(i, i);
      }
    }
    cout << sz(ans) << '\n';
    for (const auto &[l, r] : ans) {
      cout << l + 1 << ' ' << r + 1 << '\n';
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
