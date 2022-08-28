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
  int n, q; cin >> n >> q;
  vector<int> p(n);
  for (int &x : p) cin >> x, --x;
  vector<int> premax(n), r(n);
  for (int i = 0; i < n; i++) {
    if (i == 0) premax[i] = p[i];
    else premax[i] = max(premax[i - 1], p[i]);
  }
  vector<int> stk;
  for (int i = n - 1; i >= 0; i--) {
    while (!stk.empty() && p[stk.back()] < p[i]) stk.pop_back();
    r[i] = stk.empty() ? n : stk.back();
    stk.push_back(i);
  }

  for (int id, k; q--;) {
    cin >> id >> k;
    id--;

    int ans = 0;
    if (k > n - 1) {
      if (p[id] == n - 1) ans = k - (n - 1);
      k = n - 1;
    }
    if (id <= k && premax[id] == p[id]) {
      ans += int(id != 0) + min(k - id , r[id] - id - 1);
    }
    cout << ans << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
