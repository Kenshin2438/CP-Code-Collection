#include <iostream>
#include <vector>
using namespace std;

const int mod = 1000000007;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m; cin >> n >> m;
  vector<vector<vector<int>>> dp(
    n + 1, vector<vector<int>>(m + 1, vector<int>(m + 1))
  );
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (i == 0 && j == 0) {
        dp[0][0][2] = 1;
        continue;
      }
      for (int k = 0; k <= m; k++) {
        if (i > 0 && k % 2 == 0) 
          dp[i][j][k] = (dp[i][j][k] + dp[i-1][j][k/2]) % mod;
        if (j > 0 && k + 1 <= m)
          dp[i][j][k] = (dp[i][j][k] + dp[i][j-1][k+1]) % mod;
      }
    }
  }
  cout << dp[n][m-1][1] << '\n';
  return 0;
}