#define PROBLEM "http://oj.daimayuan.top/course/10/problem/504"

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

using db = long double;
using ll = long long;

void SingleTest(int TestCase) {
  int n; cin >> n;
  vec<int> a(n + 1, 0);
  for (int i = 1; i <= n; i++) cin >> a[i];
  vec<int> dp(n + 1, 0);
  map<int, int> pos;
  pos[0] = 0;
  for (int i = 1; i <= n; i++) {
    dp[i] = 1;
    if (pos.count(a[i] - 1)) {
      dp[i] += dp[ pos[a[i] - 1] ];
    }
    pos[ a[i] ] = i;
  }
  int m = 0, v = 1e9;
  for (int i = 1; i <= n; i++) {
    if (dp[i] > m) {
      m = dp[i], v = a[i];
    } else if (dp[i] == m) {
      v = min(v, a[i]);
    }
  }
  cout << m << '\n';
  for (int i = v - m + 1; i <= v; i++) {
    cout << i << " \n"[i == v];
  }
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
