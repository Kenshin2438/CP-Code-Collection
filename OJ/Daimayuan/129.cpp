#define PROBLEM "http://oj.daimayuan.top/course/11/problem/129"

#include "bits/stdc++.h"
using namespace std;

#ifdef LOCAL
  #include "debug.hpp"
#else
  #define debug(...)
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

int dp[55][5];

void SingleTest(int TestCase) {
  int n; cin >> n;
  dp[1][0] = 1;
  dp[2][0] = 2;
  dp[2][1] = 1;
  for (int i = 3; i <= n; i++) {
    
  }
  cout << (dp[n][0] + dp[n][1] + dp[n][2]);
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
