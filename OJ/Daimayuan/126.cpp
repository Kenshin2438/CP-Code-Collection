#define PROBLEM "http://oj.daimayuan.top/course/11/problem/126"

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
#define pb push_back
#define all(a) a.begin(), a.end()

typedef double db;
typedef long long ll;

const int mod = (int) 1e9 + 7;

int n, grid[250][250], dp[250][250];

void SingleTest(int TestCase) {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> grid[i][j];
    }
  }
  if (grid[1][1] == 0) return cout << 0, void();
  dp[1][1] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == 1 && j == 1) continue;

      if (grid[i][j]) {
        dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
      }
    }
  }
  cout << dp[n][n];
}

void init() { }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--; ) SingleTest(++TestCase);
  return 0;
}
