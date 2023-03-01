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
  int n, m; cin >> n >> m;
  string a, b; cin >> a >> b;

  bool ans = true;
  int cnt = 0;
  char pre = '#';
  for (int i = 0; i < n; i++) {
    if (a[i] == pre) cnt += 1;
    pre = a[i];
  }
  for (int i = m - 1; i >= 0; i--) {
    if (b[i] == pre) cnt += 1;
    pre = b[i];
  }
  ans = cnt <= 1;
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}