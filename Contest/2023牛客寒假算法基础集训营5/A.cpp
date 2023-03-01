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
  int n, Q; cin >> n >> Q;
  vector<ll> a(n);
  for (ll &x : a) cin >> x;
  sort(all(a));

  debug(a);
  vector<ll> s(n);
  partial_sum(all(a), begin(s));

  for (int k, x; Q--; ) {
    cin >> k >> x;
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