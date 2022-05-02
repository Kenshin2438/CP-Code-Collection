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
int s[N][N], dp[N][N];

// PII get(int s, int t, int cnt) {
//   int pl = -1, pr = -1;
//   if (s > t) return {pl, pr};
//   {
//     int l = s, r = t;
//     while (l <= r) {
//       int m = (l + r) >> 1;
//       if (a[t] - a[m - 1] <= cnt) {
//         r = m - 1, pl = m;
//       } else {
//         l = m + 1;
//       }
//     }
//   }
//   {
//     int l = s, r = t;
//     while (l <= r) {
//       int m = (l + r) >> 1;
//       if (a[t] - a[m - 1] >= cnt) {
//         l = m + 1, pr = m;
//       } else {
//         r = m - 1;
//       }
//     }
//   }
//   return {pl, pr};
// }

void SingleTest(int TestCase) {
  str tmp; cin >> tmp;
  n = tmp.length();
  tmp = "+" + tmp;
  for (int i = 1; i <= n; i++) {
    a[i] = a[i - 1] + (int(tmp[i] - '0') & 1);
  }
  for (int len = 1; len <= n; len++) {
    for (int i = 1, j = len; j <= n; i++, j++) {
      dp[i][j] = 1;
      int l, r; l = r = j;
      for (int k = i; k < j; k++) {
        // auto [l, r] = get(k + 1, j, a[k] - a[i - 1]);
        // debug(i, k, j, a[k] - a[i - 1], l, r);
        // if (l == -1 || r == -1) continue;
        while (l >= k + 1 && a[k] - a[i - 1] >= a[j] - a[l - 1]) l--;
        while (a[k] - a[i - 1] > a[j] - a[r - 1]) r--;
        if (r < l || r <= k) break;
        int sum = (mod + 0LL + s[k + 1][r - 1] - s[k + 1][l - 1]) % mod;
        // for (int h = l - 1; h < r; h++) {
        //   sum = (sum + dp[k + 1][h]) % mod;
        // }
        if (a[k] - a[i - 1] == a[j] - a[k]) sum++;
        dp[i][j] = (dp[i][j] + sum) % mod;
      }
      // debug(i, j, dp[i][j]);
      s[i][j] = (s[i][j - 1] + dp[i][j]) % mod;
    }
    // for (int i = 1; i <= n; i++) {
    //   for (int j = i; j <= n; j++) {
    //     s[i][j] = (s[i][j - 1] + dp[i][j]) % mod;
    //   }
    // }
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
