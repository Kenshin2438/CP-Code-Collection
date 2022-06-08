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
  int n, m; cin >> n >> m;
  // gcd(a, b) = n; lcm(a, b) = m;
  // a = A * n, b = B * n; m = A * B * n;
  int mul = m / n, ans = (int) 2e9;
  for (int x = 1; x <= mul / x; x++) {
    if (mul % x == 0 && __gcd(x, mul / x) == 1) {
      ans = min(ans, x + mul / x);
    }
  }
  cout << 1LL * n * ans << '\n';
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