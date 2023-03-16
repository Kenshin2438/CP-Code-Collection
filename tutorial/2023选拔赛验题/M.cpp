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
  int n, q; cin >> n >> q;
  assert(1 <= n && n <= (int) 1e5);
  assert(1 <= q && q <= (int) 1e5);

  vector<ll> a(n);
  for (auto &&x : a) {
    cin >> x;
    assert(1 <= x && x <= n);
    x -= 1;
  }

  vector<vector<ll>> st(31, a);
  for (int _ = 1; _ <= 30; _++) {
    for (int i = 0; i < n; i++) {
      st[_][i] = st[_ - 1][st[_ - 1][i]];
    }
  }

  for (int pos, k; q--; ) {
    cin >> pos >> k;
    assert(1 <= pos && pos <= n);
    assert(1 <= k && k <= (int) 1e9);
    int now = pos - 1;
    for (int i = 30; i >= 0; i--) {
      if (k >> i & 1) now = st[i][now];
    }
    cout << now + 1 << "\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}