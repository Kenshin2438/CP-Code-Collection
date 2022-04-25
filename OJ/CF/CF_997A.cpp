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
  ll n, x, y; str s;
  cin >> n >> x >> y >> s;
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (i == 0) {
      cnt += (int) (s[i] == '0');
    } else {
      cnt += (int) (s[i] == '0' && s[i - 1] == '1');
    }
  }
  if (cnt == 0) {
    cout << 0 << '\n';
  } else {
    cout << y + (cnt - 1) * min(x, y) << '\n';
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
