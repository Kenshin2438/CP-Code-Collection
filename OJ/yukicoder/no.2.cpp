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
  vector<int> stones;
  int n; cin >> n;
  for (int i = 2; (ll) i * i <= n; i++) {
    if (n % i == 0) {
      int cnt = 0;
      while (n % i == 0) n /= i, cnt += 1;
      stones.emplace_back(cnt);
    }
  }
  if (n != 1) stones.emplace_back(1);
  int nim = accumulate(all(stones), 0, bit_xor<int>());
  cout << (nim ? "Alice" : "Bob") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
