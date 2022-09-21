#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n; cin >> n;
  int k = int(0.5 + sqrt(n));
  vector<int> p;
  for (int i = n / k; i >= 0; i--) {
    int l = i * k + 1, r = min(l + k - 1, n);
    debug(k, i, l, r);
    for (int j = l; j <= r; j++) p.push_back(j);
  }
  for (int i = 0; i < n; i++) {
    cout << p[i] << " \n"[i + 1 == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
