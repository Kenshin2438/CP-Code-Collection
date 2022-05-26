#define PROBLEM "http://oj.daimayuan.top/course/11/problem/461"

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
  vec<tuple<int, int, int>> task(n);
  for (auto &[e, s, w] : task)
    cin >> s >> e >> w;
  sort(all(task));
  vec<int> dp(n);
  for (int i = 0; i < n; i++) {
    int tmp = get<2>(task[i]);
    dp[i] = tmp;
    for (int j = 0; j < i; j++) {
      if (get<0>(task[j]) <= get<1>(task[i])) {
        dp[i] = max(dp[i], dp[j] + tmp);
      }
    }
  }
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
