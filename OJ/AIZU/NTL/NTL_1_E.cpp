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

pair<int, int> exgcd(int a, int b) {
  bool nega = (a < 0);
  bool negb = (b < 0);
  int x = 1, y = 0;
  int r = 0, s = 1, t = 0;
  while (b) {
    r ^= x ^= r ^= x -= (t = a / b) * r;
    s ^= y ^= s ^= y -= t * s;
    b ^= a ^= b ^= a %= b;
  }
  return {nega ? -x : x, negb ? -y : y};
}

/**
which |x|+|y| is the minimal (primarily) and x ≤ y (secondarily).
**/

void SingleTest(int TestCase) {
  int a, b; cin >> a >> b;
  auto [x, y] = exgcd(a, b);
  cout << x << ' ' << y << '\n';
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
