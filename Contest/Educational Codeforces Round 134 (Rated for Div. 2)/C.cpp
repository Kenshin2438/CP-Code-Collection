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
  int n; cin >> n;

  vector<ll> a(n), b(n);
  for (ll &x : a) cin >> x;
  for (ll &x : b) cin >> x;

  vector<ll> l(n), r(n);
  for (int i = 0; i < n; i++) {
    l[i] = lower_bound(all(b), a[i]) - begin(b);
  }
  for (int i = 0, p = 0; i < n; i++) {
    while (p + 1 < n && l[p + 1] <= p) p++;
    r[i] = p;
    if (p == i) p++;
  }

  for (int i = 0; i < n; i++) {
    cout << b[ l[i] ] - a[i] << " \n"[i + 1 == n];
  }
  for (int i = 0; i < n; i++) {
    cout << b[ r[i] ] - a[i] << " \n"[i + 1 == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
