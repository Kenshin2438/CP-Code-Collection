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
  vector<int> p(n); iota(all(p), 1);

  if (n & 1) {
    for (int i = 1; i + 1 < n; i += 2) {
      swap(p[i], p[i + 1]);
    }
  } else {
    for (int i = 0; i + 1 < n; i += 2) {
      swap(p[i], p[i + 1]);
    }
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
