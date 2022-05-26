#define PROBLEM "http://oj.daimayuan.top/course/11/problem/289"

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

void SingleTest(int TestCase) {
  int n; cin >> n;
  vec<int> a(n), dp(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i]; dp[i] = a[i];
    for (int j = 0; j < i; j++) {
      if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + a[i]);
    }
  }
  // cout << dp[n - 1];
  cout << *max_element(all(dp));
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
