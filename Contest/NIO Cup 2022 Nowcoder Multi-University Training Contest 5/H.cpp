#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);

  const double pi = acos(-1);
  for (int n; cin >> n; ) {
    double r = n / 2.;
    cout << (pi * r * r / 2 + r * n) << '\n';
  }
  return 0;
}
