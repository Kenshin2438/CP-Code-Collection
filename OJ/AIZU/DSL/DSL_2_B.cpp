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
  const int B = 320;
  int n, q; cin >> n >> q;
  vec<int> sm(B, 0), a(n, 0), pos(n);
  for (int i = 0; i < n; i++) pos[i] = i / B;
  for (int op, x, y; q--; ) {
    cin >> op >> x >> y, x--, y -= op;
    if (op == 1) {
      int sum = 0;
      if (pos[x] == pos[y]) {
        for (int i = x; i <= y; i++) sum += a[i];
      } else {
        for (int i = x; pos[i] == pos[x]; i++) sum += a[i];
        for (int k = pos[x] + 1; k < pos[y]; k++) sum += sm[k];
        for (int i = y; pos[i] == pos[y]; i--) sum += a[i];
      }
      cout << sum << '\n';
    } else {
      a[x] += y, sm[pos[x]] += y;
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
