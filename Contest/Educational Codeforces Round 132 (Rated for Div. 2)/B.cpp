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
  int n, q; cin >> n >> q;
  vector<ll> h(n);
  for (ll &x : h) cin >> x;

  vector<ll> pre(n), suf(n);
  pre[0] = 0;
  for (int i = 1; i < n; i++) {
    pre[i] = max(h[i - 1] - h[i], 0LL) + pre[i - 1];
  }
  suf[n - 1] = 0;
  for (int i = n - 2; i >= 0; i--) {
    suf[i] = suf[i + 1] + max(h[i + 1] - h[i], 0LL);
  }
  debug(pre);
  debug(suf);
  while (q--) {
    int s, t; cin >> s >> t;
    --s, --t;
    if (s > t) {
      cout << suf[t] - suf[s] << '\n';
    } else {
      cout << pre[t] - pre[s] << '\n';
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
