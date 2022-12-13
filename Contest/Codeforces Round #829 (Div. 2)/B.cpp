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
  int d = n / 2;
  vector<bool> vis(n + 1, false);
  vector<int> ans;
  for (int x = d; x >= 1; x--) {
    int cur = x;
    while (cur <= n) {
      if (vis[cur] == false) ans.emplace_back(cur);
      else break;
      cur += d;
    }
  }

  for (const int &x : ans) cout << x << ' ';
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  // for (int n = 2; n <= 13; n++) {
  //   vector<int> p(n); iota(all(p), 1);
  //   int ans = 1; vector<int> _ = p;
  //   do {
  //     int d = 1000000;
  //     for (int i = 0; i + 1 < n; i++) {
  //       d = min(d, abs(p[i + 1] - p[i]));
  //     }
  //     if (d > ans) ans = d, _ = p;
  //   } while (next_permutation(all(p)));
  //   debug(n, ans, _);
  // }

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
