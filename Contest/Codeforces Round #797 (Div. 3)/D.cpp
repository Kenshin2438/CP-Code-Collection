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
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

void SingleTest(__attribute__((unused)) int TestCase) {
  int n, k; cin >> n >> k;
  str s; cin >> s;

  vec<int> sum(n);
  for (int i = 0; i < n; i++) {
    sum[i] = s[i] == 'W';
  }
  partial_sum(all(sum), begin(sum));
  // debug(sum);
  int ans = sum[k - 1];
  for (int i = k; i < n; i++) {
    ans = min(ans, sum[i] - sum[i - k]);
  }
  cout << ans << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
