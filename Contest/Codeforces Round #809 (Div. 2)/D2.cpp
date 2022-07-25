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
  int n, k; cin >> n >> k;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  a.erase(unique(all(a)), end(a));
  if (a.size() == 1 || k > a.back()) {
    return cout << 0 << '\n', void();
  }

  vector<vector<int>> v(a.back() + 1);
  for (int x : a) v[x].push_back(x);

  int l = a.front(), ans = 0x3f3f3f3f, tag = 0;
  for (int p = a.back(); p > 0 && tag == 0; p--) {
    if (v[p].empty()) continue;
    ans = min(ans, p - l);
    if (ans == 0) break;
    while (!v[p].empty()) {
      int M = v[p].back();
      int b = min(M / p + 1, k);
      if (M / b == p) {
        tag = 1;
        break;
      } else {
        v[M / b].push_back(M);
        l = min(l, M / b);
      }
      v[p].pop_back();
    }
    vector<int>().swap(v[p]);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}
