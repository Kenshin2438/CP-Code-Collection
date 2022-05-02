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
  int n, Q; cin >> n >> Q;
  vec<int> a(n);
  for (int &x : a) cin >> x;
  vec<array<int, 2>> change(31, {0, 1});
  while (Q--) {
    str op; cin >> op;
    int x;  cin >> x;
    if (op == "AND") {
      for (int i = 0; i <= 30; i++) {
        int b = x >> i & 1;
        change[i][0] &= b;
        change[i][1] &= b;
      }
    } else if (op == "OR") {
      for (int i = 0; i <= 30; i++) {
        int b = x >> i & 1;
        change[i][0] |= b;
        change[i][1] |= b;
      }
    } else {
      for (int i = 0; i <= 30; i++) {
        int b = x >> i & 1;
        change[i][0] ^= b;
        change[i][1] ^= b;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    int ans = 0;
    for (int j = 0; j <= 30; j++) {
      ans |= change[j][a[i] >> j & 1] << j;
    }
    cout << ans << " \n"[i + 1 == n];
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
