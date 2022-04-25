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
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

void SingleTest(int TestCase) {
  int n, m, a, b;
  cin >> n >> m >> a >> b;

  for (int i = 1; i <= b; i++) {
    for (int j = 1; j <= a; j++) {
      cout << "1";
    }
    for (int j = a + 1; j <= m; j++) {
      cout << "0";
    }
    cout << '\n';
  }
  for (int i = b + 1; i <= n; i++) {
    for (int j = 1; j <= a; j++) {
      cout << "0";
    }
    for (int j = a + 1; j <= m; j++) {
      cout << "1";
    }
    cout << '\n';
  }
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
