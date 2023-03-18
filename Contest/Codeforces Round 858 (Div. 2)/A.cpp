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
  ll a, b, c, d; cin >> a >> b >> c >> d;

  if (d < b) {
    cout << "-1\n";
    return;
  }

  ll dy = d - b;
  if (a + dy < c) {
    cout << "-1\n";
    return;
  }
  ll dx = a + dy - c;

  cout << dy + dx << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}