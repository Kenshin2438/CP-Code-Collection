#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

const int mod = 998244353;
const int N = 505;

int n, a[N];
int dp[N][N], s[N][N][N];

void SingleTest(int TestCase) {
  str tmp; cin >> tmp;
  n = tmp.length();
  tmp = "+" + tmp;
  for (int i = 1; i <= n; i++) {
    a[i] = a[i - 1] + (int(tmp[i] - '0') & 1);
  }
  for (int len = 1; len <= n; len++) {
    for (int i = 1, j = len; j <= n; j++, i++) {
      dp[i][j] = 1;
      for (int k = i; k < j; k++) {
        dp[i][j] += int(a[j] - a[k] == a[k] - a[i - 1]);
      }
      for (int k = i; k < j; k++) {
        int m = a[k] - a[i - 1];
        dp[i][j] = (dp[i][j] + s[k + 1][j][m]) % mod;
      }
      for (int k = i; k < j; k++) {
        int m = a[j] - a[k];
        s[i][j][m] = (s[i][j][m] + dp[i][k]) % mod;
      }
    }
  }
  cout << dp[1][n] << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
