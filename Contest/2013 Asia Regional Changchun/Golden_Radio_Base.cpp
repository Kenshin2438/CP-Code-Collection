#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  const int N = 200, EPS = 100;
  for (int n; cin >> n; ) {
    vector<int> a(N);
    a[0 + EPS] = n;

    while (true) {
      bool changed = false;
      for (int i = 2; i + 1 < N; i++) {
        if (a[i] > 1) {
          changed = true;
          a[i - 2] += a[i] / 2, a[i + 1] += a[i] / 2, a[i] %= 2;
        }
      }
      if (changed == false) break;
      for (int i = 0; i + 1 < N; i++) {
        if (a[i] && a[i + 1]) {
          int d = min(a[i], a[i + 1]);
          a[i] -= d, a[i + 1] -= d, a[i + 2] += d;
        }
      }
    }

    int l = 0, r = N - 1;
    while (l < r && a[l] == 0) l += 1;
    while (l < r && a[r] == 0) r -= 1;
    for (int i = r; i >= l; i--) {
      if (i == -1 + EPS) cout << '.';
      cout << a[i];
    }
    cout << '\n';
  }

  return 0;
}
