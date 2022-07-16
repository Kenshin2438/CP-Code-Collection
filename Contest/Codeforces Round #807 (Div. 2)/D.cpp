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
  string s, t; cin >> s >> t;
  if (s.front() != t.front() || s.back() != t.back()) {
    return cout << "-1\n", void();
  }
  /**
   * 001 <-> 011
   * 100 <-> 110
   */
  vector<pair<int, int>> ls, lt;
  {
    int l = -1, r = -1;
    for (int i = 0; i < n; i++) {
      if (s[i] == '0') {
        if (l != -1 && r != -1) {
          ls.emplace_back(l, r);
        }
        l = r = -1;
      } else {
        if (l == -1) l = i;
        r = i;

        if (i == n - 1) {
          ls.emplace_back(l, r);
        }
      }
    }
  }
  {
    int l = -1, r = -1;
    for (int i = 0; i < n; i++) {
      if (t[i] == '0') {
        if (l != -1 && r != -1) {
          lt.emplace_back(l, r);
        }
        l = r = -1;
      } else {
        if (l == -1) l = i;
        r = i;

        if (i == n - 1) {
          lt.emplace_back(l, r);
        }
      }
    }
  }
  if (ls.size() != lt.size()) {
    return cout << "-1\n", void();
  }
  // debug(ls);
  // debug(lt);
  ll ans = 0LL;
  for (int i = 0; i < ls.size(); i++) {
    auto [Ls, Rs] = ls[i];
    auto [Lt, Rt] = lt[i];
    ans += abs(Ls - Lt) + abs(Rs - Rt);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}