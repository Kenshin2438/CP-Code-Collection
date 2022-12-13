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
  using BS = bitset<3005>;

  int n, m; cin >> n >> m;
  vector<BS> grid(n);
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    for (int j = 0; j < m; j++) {
      grid[i].set(j, s[j] == 'z');
    }
  }

  vector<BS> a(n), b(n);
  for (int i = 0; i < n; i++) {
    a[i].set(), b[i].set();
  }

  ll ans = 0LL;
  for (int len = 1; len <= min(n, m); len++) {
    for (int i = 0; i < n; i++) {
      a[i] &= grid[i] << (len - 1);
    }
    for (int i = 0; i + len - 1 < n; i++) {
      b[i] &= grid[i + len - 1] << (len - 1);
      ans += (a[i] & a[i + len - 1] & b[i]).count();
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
