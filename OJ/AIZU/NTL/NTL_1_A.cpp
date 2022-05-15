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
  int _ = n;
  vec<int> fac;
  for (int i = 2, m = sqrt(n) + 1; i <= m; i++) {
    while (n % i == 0) fac.push_back(i), n /= i;
  }
  if (n > 1) fac.push_back(n);
  sort(all(fac));
  cout << _ << ":";
  for (const int &x : fac) cout << " " << x;
  cout << '\n';
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
