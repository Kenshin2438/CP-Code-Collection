/*******************************
| Author:  Kenshin2438
| Problem: G - Divide a Sequence
| Contest: AtCoder - AtCoder Beginner Contest 234
| URL:     https://atcoder.jp/contests/abc234/tasks/abc234_g
| When:    2022-03-11 19:35:28
|
| Memory:  1024 MB
| Time:    2000 ms
*******************************/

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

const int N = (int) 3e5 + 10;
const int mod = 998244353;
 
int n, a[N];
ll dp[N], smax[N], smin[N], pre[N];
stack<int> mx, mi;
 
void SingleTest(int TestCase) {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  pre[0] = dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    ll sm = 0, si = 0;
    while (!mx.empty() && a[mx.top()] <= a[i]) mx.pop();
    if (mx.empty()) {
      sm = pre[i - 1] * a[i] % mod;
    } else {
      sm = ((pre[i - 1] - pre[mx.top() - 1]) % mod + mod) * a[i] % mod;
      sm = (sm + smax[mx.top()]) % mod;
    }
    mx.push(i);
 
    while (!mi.empty() && a[mi.top()] >= a[i]) mi.pop();
    if (mi.empty()) {
      si = pre[i - 1] * a[i] % mod;
    } else {
      si = ((pre[i - 1] - pre[mi.top() - 1]) % mod + mod) * a[i] % mod;
      si = (si + smin[mi.top()]) % mod;
    }
    mi.push(i);
 
    dp[i] = ((sm - si) % mod + mod) % mod;
    smin[i] = si, smax[i] = sm;
    pre[i] = (pre[i - 1] + dp[i]) % mod;
  }
  cout << dp[n];
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
