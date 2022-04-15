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
  const int B = 320, inf = numeric_limits<int>::max();
  int n, q; cin >> n >> q;
  vec<int> mi(B, inf), a(n, inf), pos(n);
  for (int i = 0; i < n; i++) pos[i] = i / B;
  for (int op, x, y; q--; ) {
    cin >> op >> x >> y;
    if (op == 1) {
      int ans = inf;
      if (pos[x] == pos[y]) {
        for (int i = x; i <= y; i++) ans = min(ans, a[i]);
      } else {
        for (int i = x; pos[i] == pos[x]; i++) ans = min(ans, a[i]);
        for (int k = pos[x] + 1; k < pos[y]; k++) ans = min(ans, mi[k]);
        for (int i = y; pos[i] == pos[y]; i--) ans = min(ans, a[i]);
      }
      cout << ans << '\n';
    } else {
      mi[pos[x]] = a[x] = y;
      for (int i = pos[x] * B; i < n && pos[i] == pos[x]; i++) {
        mi[pos[x]] = min(mi[pos[x]], a[i]);
      }
    }
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
