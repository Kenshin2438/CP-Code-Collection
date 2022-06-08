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
  int n; cin >> n;

  int h1, h2, h3;
  for (int i = 1; i <= n; i++) {
    int tmp = n - i;
    int a = tmp / 2, b = tmp - a;
    if (a == b) {
      a--, b++;
    }
    if (a >= 1 && b >= 1 && b < i && a < b) {
      h1 = i, h2 = b, h3 = a;
      break;
    }
  }
  cout << h2 << ' ' << h1 << ' ' << h3 << '\n';
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
