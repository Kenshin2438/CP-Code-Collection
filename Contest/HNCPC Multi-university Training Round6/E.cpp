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
#define all(a) a.begin(), a.end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

void SingleTest(int TestCase) {
  str s; cin >> s;
  int n = s.length();
  vec<ll> dp(3);
  for (int i = 0; i < n; i++) {
    if (s[i] == 'a') dp[0]++;
    if (s[i] == 'h') {
      dp[2] += dp[1];
      dp[1] += dp[0];
    }
  }
  cout << dp[2] << '\n';
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
