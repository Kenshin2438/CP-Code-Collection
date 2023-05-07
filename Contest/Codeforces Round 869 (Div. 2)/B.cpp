#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
//   int n; cin >> n;
//   vector<int> p(n); iota(all(p), 1);
//   do { 
//     bool ok = true;
//     for (int len = 2; len <= n; len++) {
//       for (int l = 0, r = len - 1; r < n; l++, r++) {
//         int SUM = accumulate(begin(p) + l, begin(p) + l + len, 0);
//         if (SUM % len == 0) { ok = false; goto B; }
//       }
//     }
// B:
//     if (ok == true) debug(n, p);
//   } while (next_permutation(all(p)));

  int n; cin >> n;
  if (n == 1) return cout << "1\n", void();
  if (n % 2 == 0) {
    for (int i = 1; i <= n; i += 2) {
      cout << i + 1 << ' ' << i << ' ';
    }
    cout << '\n';
  } else {
    cout << "-1\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}