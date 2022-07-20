#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;

void solve() {
  int n; cin >> n;
  vector<ll> cnt(n + 1);
  for (int i = 0; i <= n; i++) {
    cin >> cnt[i];
  }
  for (int i = n; i >= 1; i--) {
    cnt[i - 1] += cnt[i] / 2;
  }
  cout << ((cnt[0] > 0) ? "Alice" : "Bob") << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}