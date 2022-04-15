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

using db = double;
using ll = long long;

const int N = (int) 5e3 + 10;
const int mod = 998'244'353;

ll bino[N][N], dp[N][N];
int n, a[N], pre[N];

ll C(int a, int b) {
  if (a < 0 || b < 0) return 0;
  return bino[a][b];
}

ll sol(int p, int len) {
  if (p == 0 && len == n / 2) return 1;
  if (p == 0) return 0;
  if (~dp[p][len]) return dp[p][len];

  int cnt = p - pre[p];
  int num = (len - 1) - (n - p - len) + (len == n / 2);
  ll Y = 0, N = 0;

  N = C(num, cnt) * sol(pre[p], len) % mod;
  if (len < n / 2) Y = C(num, cnt - 1) * sol(pre[p], len + 1) % mod;
  return dp[p][len] = (N + Y) % mod;
}

void SingleTest(int TestCase) {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= n; i++) {
    pre[i] = (a[i] == a[i - 1]) ? pre[i - 1] : (i - 1);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      dp[i][j] = -1;
    }
  }
  if (a[n] == a[n - 1]) return cout << 0 << '\n', void();
  cout << sol(n - 1, 1) << '\n';
}

void init() {
  for (int i = 0; i <= 5000; i++) {
    bino[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      bino[i][j] = (bino[i - 1][j] + bino[i - 1][j - 1]) % mod;
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
