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

const int N = 3e5 + 10;
ll dp[N];
void init() {
  memset(dp, 0x3f, sizeof dp);
  dp[1] = 0;
  for (int i = 2; i < N; i++) {
    for (int j = i; j < N; j += i) {
      dp[j] = min(dp[j], dp[j / i] + i);
    }
  }
}

void solve() {
  int n; cin >> n;
  cout << dp[n] << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init();

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
