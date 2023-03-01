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
  string s; cin >> s;

  int pre = 0, cnt = 0;
  for (int i = 0, j = n - 1; i < j; i++, j--) {
    int now = s[i] != s[j];
    if (pre == 0 && now == 1) cnt ++;
    pre = now;
  }
  cout << (cnt <= 1 ? "YES" : "NO") << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}