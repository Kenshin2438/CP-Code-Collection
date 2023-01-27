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
  if (n < 4 || n == 7) return cout << "-1\n", void();
  vector<int> p(n); iota(all(p), 1);
  if (n % 4 == 0) {
    for (int i = 0; i < n; i = i + 4) {
      swap(p[i], p[i + 2]);
      swap(p[i + 1], p[i + 3]);
    }
  } else if (n % 4 == 1) {
    p[0] = 3;
    p[1] = 4;
    p[2] = 5;
    p[3] = 1;
    p[4] = 2;
    for (int i = 5; i < n; i = i + 4) {
      swap(p[i], p[i + 2]);
      swap(p[i + 1], p[i + 3]);
    }
  } else if (n % 4 == 2) {
    p[0] = 3;
    p[1] = 5;
    p[2] = 1;
    p[3] = 6;
    p[4] = 2;
    p[5] = 4;
    for (int i = 6; i < n; i = i + 4) {
      swap(p[i], p[i + 2]);
      swap(p[i + 1], p[i + 3]);
    }
  } else {
    p[0] = 3;
    p[1] = 5;
    p[2] = 1;
    p[3] = 6;
    p[4] = 2;
    p[5] = 4;

    p[6]  = 9;
    p[7]  = 10;
    p[8]  = 11;
    p[9]  = 7;
    p[10] = 8;
    for (int i = 11; i < n; i = i + 4) {
      swap(p[i], p[i + 2]);
      swap(p[i + 1], p[i + 3]);
    }
  }
  for (int i = 0; i < n; i++) {
    cout << p[i] << " \n"[i + 1 == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}