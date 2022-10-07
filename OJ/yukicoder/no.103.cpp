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
  const int N = 1e4 + 1;
  array<vector<int>, N> pfac;
  for (int i = 2; i < N; i++) {
    int n = i;
    for (int d = 2; d * d <= n; d++) {
      if (n % d == 0) pfac[i].emplace_back(d);
      while (n % d == 0) n /= d;
    }
    if (n != 1) pfac[i].emplace_back(n);
  }

  array<int, N> grundy;
  for (int i = 2; i < N; i++) {
    int mex[100] = {};
    for (const int &d : pfac[i]) {
      mex[grundy[i / d]] += 1;
      if (i % (d * d) == 0) {
        mex[grundy[i / (d * d)]] += 1;
      }
      while (mex[grundy[i]]) grundy[i] += 1;
    }
  }

  int n; cin >> n;
  int nim = 0;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    nim ^= grundy[x];
  }
  cout << (nim ? "Alice" : "Bob") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
