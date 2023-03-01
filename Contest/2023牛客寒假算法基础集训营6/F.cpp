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
  priority_queue<int> pq;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    pq.emplace(x);
  }

  map<int, int> ans;
  ans[0] = pq.top();
  for (int t = 1; pq.top() > 1; t++) {
    int x = pq.top(); pq.pop();
    pq.push(__builtin_popcount(x));
    if (pq.top() != x) ans[t] = pq.top();
  }
  debug(ans);

  for (int k; q--;) {
    cin >> k;
    cout << prev(ans.upper_bound(k))->second << '\n';
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