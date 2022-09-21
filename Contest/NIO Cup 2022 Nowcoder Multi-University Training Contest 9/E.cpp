#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) static_cast<int>(size(x))

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int m; cin >> m;

  int h = 32 - __builtin_clz(m);
  vector<int> a, b;
  for (int i = 0; i < h; i++) {
    a.emplace_back(i * 200);
    if (i != 0) a.emplace_back(i * 200 - 100);
  }
  debug(h, a);
  for (int have = 0, i = h - 1; i >= 0; i--) {
    debug(i, m >> i & 1);
    have += 1;
    if (m >> i & 1) {
      int LIM = a[max(0, i * 2 - 1)] + have + 10;
      while (have) b.emplace_back(--LIM), have -= 1;
    }
  }
  reverse(all(b));
  debug(a, b);
  vector<int> ans;
  for (const int &x : a) ans.emplace_back(x);
  for (const int &x : b) ans.emplace_back(x);
  vector<int> tmp = ans;
  sort(all(tmp));
  cout << sz(ans) << '\n';
  for (const int &x : ans) {
    cout << int(lower_bound(all(tmp), x) - begin(tmp) + 1) << ' ';
  }
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
