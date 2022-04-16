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

const int N = (int) 1e3 + 10;

int num[N][N];

void SingleTest(int TestCase) {
  int n; cin >> n;
  for (int x1, y1, x2, y2; n--; ) {
    cin >> x1 >> y1;
    cin >> x2 >> y2;
    num[x1][y1]++, num[x2][y2]++;
    num[x1][y2]--, num[x2][y1]--;
  }
  for (int i = 0; i <= 1000; i++) {
    for (int j = 0; j <= 1000; j++) {
      num[i][j + 1] += num[i][j];
    }
  }
  for (int i = 0; i <= 1000; i++) {
    for (int j = 0; j <= 1000; j++) {
      num[i + 1][j] += num[i][j];
    }
  }
  int ans = 0;
  for (int i = 0; i <= 1001; i++) {
    ans = max(ans, *max_element(num[i], num[i] + 1002));
  }
  cout << ans << '\n';
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
