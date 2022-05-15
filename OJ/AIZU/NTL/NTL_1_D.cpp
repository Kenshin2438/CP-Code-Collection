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

int phi(int n) {
  int res = n;
  for (int i = 2; i <= n / i; i++) {
    if (n % i == 0) {
      res = res / i * (i - 1);
      while (n % i == 0) n /= i;
    }
  }
  if (n > 1) res = res / n * (n - 1);
  return res;
}

void SingleTest(int TestCase) {
  int n; cin >> n;
  cout << phi(n) << '\n';
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
