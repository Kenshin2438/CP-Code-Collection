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
  assert(2 <= n && n <= (int) 5e5);
  vector<ll> a(n);
  for (auto && x : a) {
    cin >> x;
    assert(1 <= x && x<= (int) 1e9);
  }
  cout << accumulate(all(a), 0LL) - 2 * *min_element(all(a)) << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}