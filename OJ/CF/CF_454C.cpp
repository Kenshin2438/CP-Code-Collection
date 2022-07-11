#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);

  int m, n; cin >> m >> n;
  double ans = 0.0, pre = 0;
  for (int i = 1; i <= m; i++) {
    double cur = pow(1.0 * i / m, n); 
    ans += i * (cur - pre);
    pre = cur;
  }
  cout << ans << '\n';
  return 0;
}