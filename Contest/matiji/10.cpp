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
  const function<pair<int, int> (int, int)> pos = [&](int n, int x) {
    if (x >= 1 && x <= n) return pair<int, int>{1, x};
    if (x >= n + 1 && x <= 2 * n - 1) return pair<int, int>{x - n + 1, n};
    if (x >= 2 * n && x <= 3 * n - 2) return pair<int, int>{n, 3 * n - 2 - x + 1};
    if (x >= 3 * n - 1 && x <= 4 * n - 4) return pair<int, int>{4 * n - 4 - x + 2, 1};

    auto tmp = pos(n - 2, x - 4 * n + 4);
    tmp.first += 1, tmp.second += 1;
    return tmp;
  };

  int n, x; cin >> n >> x;
  auto ans = pos(n, x);
  cout << ans.first << ' ' << ans.second << '\n';
}

int main() {
  // cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
