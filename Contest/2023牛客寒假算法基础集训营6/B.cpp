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
  int n, q; cin >> n >> q;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  static constexpr int M = 4e5 + 10;
  vector<vector<tuple<int, bool, int>>> que(M);

  for (int op, x, _ = 0; _ < q; _++) {
    cin >> op >> x;
    if (op == 1) {
      a.emplace_back(x);
    } else {
      x -= 1;
      que[x].emplace_back(a[x], true, _);
      que[sz(a) - 1].emplace_back(a[x], false, _);
    }
  }

  vector<int> cnt(M);
  map<int, int> ans;
  for (int i = 0; i < sz(a); i++) {
    int tmp = a[i];
    for (int x = 1; x * 1LL * x <= tmp; x++) {
      if (tmp % x == 0) {
        cnt[x] += 1;
        int y = tmp / x;
        cnt[y] += (x != y);
      }
    }

    for (const auto &[val, st, id] : que[i]) {
      if (st) {
        ans[id] = -cnt[val];
      } else {
        ans[id] += cnt[val];
      }
    }
  }

  debug(ans);
  for (const auto &[_, num] : ans) 
    cout << num << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}