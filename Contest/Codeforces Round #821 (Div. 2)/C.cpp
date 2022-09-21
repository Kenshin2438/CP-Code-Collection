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

  if (is_sorted(all(a))) return cout << "0\n", void();

  vector<vector<int>> pos(2);
  for (int i = 0; i < n; i++) {
    pos[a[i] & 1].push_back(i);
  }
  int B = a[0] & 1;
  vector<pair<int, int>> ans;
  for (int i = 0; i < sz(pos[B]) - 1; i++) {
    ans.emplace_back(pos[B][i] + 1, pos[B].back() + 1);
  }
  for (int i = 0; i < sz(pos[B ^ 1]); i++) {
    ans.emplace_back(1, pos[B ^ 1][i] + 1);
  }

  cout << sz(ans) << '\n';
  for (const auto &[l, r] : ans) cout << l << ' ' << r << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
