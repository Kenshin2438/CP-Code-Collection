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
  int n; cin >> n;
  int l1, r1; cin >> l1 >> r1;
  int l2, r2; cin >> l2 >> r2;

  int ans = 0;
  int l = n - r1, r = n - l1;

  auto U = [](int a, int b, int c, int d) {
    return max(0, min(b, d) - max(a, c) + 1);
  };

  cout << U(l, r, l2, r2) << '\n';
} 

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}