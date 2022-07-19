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
  int n, m; cin >> n >> m;
  string s(m, 'B');
  for (int i = 0; i < n; i++) {
    int a; cin >> a;
    int x = min(a - 1, m - a);
    int y = x ^ (a - 1) ^ (m - a);
    if (s[x] == 'A') s[y] = 'A';
    else s[x] = 'A';
  }
  cout << s << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve(); 
 
  return 0;
}