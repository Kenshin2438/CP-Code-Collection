#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  for (ll n, k; cin >> n >> k; ) {
    if (n - k > k) cout << 2 * (n - k);
    else cout << -1;

    cout << '\n';
  }

  return 0;
}
