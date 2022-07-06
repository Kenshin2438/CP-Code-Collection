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
  int n, m; cin >> n >> m;
  vector<int> a(n);
  vector<bool> have(m + 1, false);
  for (int &x : a) {
    cin >> x, have[x] = true;
  }

  int l = *min_element(all(a));
  int r = *max_element(all(a));
  int ans = r - l;

  vector<int> vis(m + 1);
  vector<int> dp(m + 1);
  for (int i = 0; i <= m; i++) {
    dp[i] = i; // init
    if (have[i]) vis[ dp[i] ] ++;
  }

  for (int i = sqrt(m); i >= 1; i--) { // min
    for (int j = i; j <= m; j += i) {
      if (have[j]) vis[ dp[j] ] --;
      if (dp[j / i] >= i) {
        dp[j] = min(dp[j], dp[j / i]);
      }
      if (have[j]) vis[ dp[j] ] ++;
    }
    while (vis[r] == 0) -- r;
    ans = min(ans, r - min(l, i));
  }
  cout << ans << '\n'; 
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) solve();
  return 0;
}