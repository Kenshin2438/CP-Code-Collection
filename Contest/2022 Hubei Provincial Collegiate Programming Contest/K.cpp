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
  ll x; db c;
  cin >> x >> c;

  db ans = 0;

  if (x >= 1e7) ans = 2.0 + c;
  else if (x <= 9'800'000) {
    ans = (1.0 * x - 9'500'000) / 300'000 + c;
  } else {
    ans = 1.0 + (1.0 * x - 9'800'000) / 200'000 + c;
  }

  cout << max(ans, 0.0) << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}