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

void SingleTest(int TestCase) {
  int n; cin >> n;
  set<tuple<ll, ll, ll>> line;
  for (ll x1, x2, y1, y2; n--; ) {
    cin >> x1 >> y1 >> x2 >> y2;
    ll A = x2 - x1;
    ll B = y2 - y1;
    ll C = x1 * y2 - y1 * x2;
    ll g = __gcd(__gcd(A, B), C);
    A /= g, B /= g, C /= g;
    if (C < 0) A *= -1, B *= -1, C *= -1;
    line.insert({A, B, C});
  }
  cout << line.size();
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
