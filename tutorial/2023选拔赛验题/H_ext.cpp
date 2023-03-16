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
  vector<int> h(n);
  for (int &x : h) cin >> x;
  vector<array<int, 3>> query(q);
  for (int i = 0; i < q; i++) {
    int pos, k; cin >> pos >> k;
    query[i][0] = h[pos - 1] + k;
    query[i][1] = pos - 1;
    query[i][2] = i;
  }

  vector<int> index(n); iota(all(index), 0);
  sort(all(index), [&](int a, int b) {
    return h[a] > h[b];
  });
  vector<int> ans(q, -1);
  sort(all(query), [&](array<int, 3> a, array<int, 3> b) {
    return a[0] > b[0];
  });

  for (const auto &[lim, pos, qid] : query) {
    static set<int> S{-2};
    for (static int i = 0; i < n; i++) {
      if (h[index[i]] <= lim) break;
      S.insert(index[i]);
    }
    ans[qid] = 1 + *prev(S.lower_bound(pos));
  }
  for (const int &x : ans) cout << x << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}