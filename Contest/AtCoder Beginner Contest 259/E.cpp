#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  int n; cin >> n;

  map<int, int> pos;
  vector<vector<pair<int, int>>> E; 

  set<int> S;
  for (int i = 0; i < n; i++) {
    int m; cin >> m;
    while (m--) {
      int p, e; cin >> p >> e;
      if (pos.count(p)) {
        E[ pos[p] ].emplace_back(e, i);
      } else {
        pos[p] = E.size();
        E.push_back(vector<pair<int, int>>{ {e, i} });
      }
    }
  }
  for (auto &&v : E) {
    sort(all(v), greater<pair<int, int>>());
    debug(v);
    if (v.size() == 1) {
      S.insert(v.front().second);
    } else {
      if (v[0].first == v[1].first) continue;
      S.insert(v.front().second);
    }
  }
  debug(S);
  cout << min(n, (int) S.size() + 1) << '\n';
  return 0;
}