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
  int x = 0, y = 0;
  for (int i = 0; i < n * n - 1; i++) {
    string s; cin >> s;
    for (const char &c : s) {
      x += c == '1';
      y += c == '2';
    }
  }
  debug(x, y);
  cout << 10 + x - y << '\n';
} 

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}