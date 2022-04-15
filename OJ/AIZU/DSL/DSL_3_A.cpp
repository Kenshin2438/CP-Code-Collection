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
  int n, s; cin >> n >> s;
  vec<int> a(n);
  for (auto &x : a) cin >> x;
  int ans = (int) 1e9;
  for (int S = 0, l = 0, r = 0; r < n; r++) {
    S += a[r];
    while (S >= s) {
      ans = min(ans, r - l + 1);
      S -= a[l ++];
    }
  }
  cout << (ans == (int) 1e9 ? 0 : ans) << '\n';
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
