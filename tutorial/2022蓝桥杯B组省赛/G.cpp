#include <iostream>
#include <vector>
using namespace std;

const int mod = 1000000007;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n; cin >> n;
  if (n == 1) return cout << 1 << '\n', 0;
  vector<long long> dp = {1, 1, 1, 2};
  for (int i = 3; i <= n; i++) {
    vector<long long> ndp(4);
    ndp[0] = dp[3];
    ndp[1] = (dp[0] + dp[2]) % mod;
    ndp[2] = (dp[0] + dp[1]) % mod;
    ndp[3] = (dp[0] + dp[1] + dp[2] + dp[3]) % mod;
    dp = move(ndp);
  }
  cout << dp[3] << '\n';
  return 0;
}