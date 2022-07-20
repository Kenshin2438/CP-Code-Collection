#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

const int N = 1 << 10;

void solve() {
  int n, m; cin >> n >> m;
  vector<bitset<N>> dp(N);
  dp[0][0] = 1;
  for (int i = 0; i < n; i++) {
    int v, w; cin >> v >> w;
    auto ndp = dp;
    for (int j = 0; j < N; j++) {
      ndp[j] |= dp[j ^ w] << v;
    }
    dp = move(ndp);
  }
  for (int i = N - 1; i >= 0; i--) {
    if (dp[i][m]) return cout << i << '\n', void();
  }
  cout << -1 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();
  
  return 0;
}