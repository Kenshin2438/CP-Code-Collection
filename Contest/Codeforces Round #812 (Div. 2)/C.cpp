#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

/**
L  P
1  {0}
2  {1, 0}
3  {1, 0, 2}
4  {0, 3, 2, 1}
5  {4, 3, 2, 1, 0}
6  {0, 3, 2, 1, 5, 4}
7  {1, 0, 2, 6, 5, 4, 3}
8  {1, 0, 7, 6, 5, 4, 3, 2}
9  {0, 8, 7, 6, 5, 4, 3, 2, 1}
10 {0, 8, 2, 6, 5, 4, 3, 9, 1, 7}
11 {0, 3, 2, 1, 5, 4, 10, 9, 8, 7, 6}
12 {4, 3, 2, 1, 0, 11, 10, 9, 8, 7, 6, 5}
13 {0, 3, 2, 1, 12, 11, 10, 9, 8, 7, 6, 5, 4}
**/

void solve() {
  int n; cin >> n;
  vector<int> p(n);

  int LIM = n - 1;
  for (int k = n - 1; k >= 0;) {
    int S = sqrt(k);
    if (S * S < k) S += 1;
    S *= S;
    auto TT = (S - k - 1);
    for (int i = S - k; i + k == S && i <= LIM && k >= 0; i++, k--) {
      debug(i, k);
      p[k] = i;
    }
    LIM = TT;
  }

  for (const int &x : p) cout << x << ' ';
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
