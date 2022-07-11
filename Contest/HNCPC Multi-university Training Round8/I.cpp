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

void SingleTest(int TestCase) {
  int n; cin >> n;
  vec<array<ll, 2>> s(n + 1);
  for (int i = 1; i <= n; i++) {
    int num; char color;
    cin >> num >> color;
    s[i][0] = s[i - 1][0];
    s[i][1] = s[i - 1][1];

    s[i][color == 'W'] += num;
  }
  if (s[n][0] == 0 || s[n][1] == 0) {
    cout << s[n][0] + s[n][1] << '\n';
    return ;
  }
  ll A = s[n][0], B = s[n][1], g = __gcd(A, B);
  A /= g, B /= g; // y = A/B * x
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i][0] == s[i - 1][0]) {
      ll tmp = s[i][0] * B;
      if (tmp % A == 0) {
        tmp /= A;
        ans += (tmp > s[i - 1][1] && tmp <= s[i][1]);
      }
    } else {
      ll tmp = s[i][1] * A;
      if (tmp % B == 0) {
        tmp /= B;
        ans += (tmp > s[i - 1][0] && tmp <= s[i][0]);
      }
    }
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
