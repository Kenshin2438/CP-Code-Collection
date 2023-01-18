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
  int n, p; cin >> n >> p;
  vector<int> a(n);
  vector<int> cnt(p);
  for (int &x : a) {
    cin >> x;
    cnt[x %= p] += 1;
  }
  vector<ll> dp(p);
  for (int vi = 0; vi < p; vi++) {
    for (int vj = 0; vj < p; vj++) {
      if (vi == vj) {
        dp[vi * vj % p] += (cnt[vi] - 1) * cnt[vi];
      } else {
        dp[vi * vj % p] += cnt[vi] * cnt[vj];
      }
    }
  }
  vector<ll> ans(p);
  for (int i = 0; i < n; i++) {
    int vk = a[i] % p;
    cnt[vk] -= 1;
    auto back = dp;
    for (int v = 0; v < p; v++) {
      dp[v * vk % p] -= cnt[v] * 2;
    }
    for (int vij = 0; vij < p; vij++) {
      ans[(vij + vk) % p] += dp[vij];
    }
    cnt[vk] += 1;
    dp = back;
  }
  for (int i = 0; i < p; i++) {
    cout << ans[i] << " \n"[i + 1 == p];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}