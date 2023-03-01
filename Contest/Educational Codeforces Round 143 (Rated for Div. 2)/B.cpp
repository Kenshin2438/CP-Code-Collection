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
  int n, k; cin >> n >> k;
  vector<pair<int, int>> p(n);
  for (auto &&[l, r] : p) cin >> l >> r;

  bool ans = false;
  int L = 0, R = 0;
  for (int i = 0; i < n; i++) {
    if (p[i].second == k) L += 1;
    if (p[i].first == k) R += 1;
  }
  ans = L > 0 && R > 0;
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}