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

void solve() {
  double A0 = 0, B0 = 0, A = 0, B = 0;
  int a, b, c, d, e;
  {
    cin >> a >> b >> c >> d >> e;
    A0 += a * 1.0 + b * 1.0 + c * 0.8 + d * 0.5;
    A += (a + b + c + d + e) * 1.0;
  }
  {
    cin >> a >> b >> c >> d >> e;
    A0 += a * 2.0 + b * 2.0 + c * 1.6 + d * 1.0;
    A += (a + b + c + d + e) * 2.0;
  }
  {
    cin >> a >> b >> c >> d >> e;
    A0 += a * 3.0 + b * 3.0 + c * 2.4 + d * 1.5;
    A += (a + b + c + d + e) * 3.0;
  }
  {
    cin >> a >> b >> c >> d >> e;
    A0 += a * 5.0 + b * 5.0 + c * 2.5 + d * 2.0;
    A += (a + b + c + d + e) * 5.0;

    B0 += a * 1.0 + b * 0.5 + c * 0.4 + d * 0.3;
    B +=(a + b + c + d + e) * 1.0;
  }

  cout << (A0 / A * 100 + B0 / B) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
