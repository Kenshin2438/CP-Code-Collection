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
  int n, q; cin >> q >> n;

  const int N = 5e4 + 500;
  bitset<N> ok; ok[0] = 1;

  for (int x; n--;) {
    cin >> x;
    for (int i = 0; i <= N; i += x) {
      ok |= ok << i;
    }
  }

  vector<int> ans(N);
  for (int i = N - 2; i >= 0; i--) {
    if (ok.test(i)) ans[i] = 0;
    else ans[i] = ans[i + 1] + 1;
  }

  for (int w; q--;) {
    cin >> w;
    cout << ans[w] << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
