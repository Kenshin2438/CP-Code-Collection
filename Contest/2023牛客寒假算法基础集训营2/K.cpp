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
  int n, m, q; cin >> n >> m >> q;
  vector<pair<int, int>> rela;
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    rela.emplace_back(a - 1, b - 1);
  }
  vector<vector<int>> que(n);
  for (int i = 0; i < q; i++) {
    int k; cin >> k;
    for (int x; k--;) {
      cin >> x;
      que[x - 1].emplace_back(i);
    }
  }
  vector<unordered_set<int>> t(n);
  for (int i = 0; i < n; i++) {
    for (const int &qq : que[i]) t[i].insert(qq);
  }
  vector<int> ans(q);
  for (auto &&[a, b] : rela) {
    if (sz(que[a]) < sz(que[b])) swap(a, b);
    for (const int &qq : que[b]) {
      if (t[a].find(qq) != t[a].end()) ans[qq] += 1;
    }
  }
  for (int i = 0; i < q; i++) {
    cout << ans[i] << "\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}