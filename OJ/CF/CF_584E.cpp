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
  int n; cin >> n;
  vector<int> p(n), s(n);
  for (int &x : p) cin >> x, -- x;
  for (int &x : s) cin >> x, -- x;
  
  vector<int> mp(n), q(n);
  for (int i = 0; i < n; i++) mp[ s[i] ] = i;
  for (int i = 0; i < n; i++) q[i] = mp[ p[i] ];
  vector<int> pos(n);
  for (int i = 0; i < n; i++) {
    pos[ q[i] ] = i;
  }
  // debug(q); debug(pos);
  ll S = 0LL;
  vector<pair<int, int>> ans;
  for (int i = 0; i < n; i++) {
    if (pos[i] == i) continue;
    for (int j = pos[i] - 1; j >= 0; j--) {
      if (q[j] >= pos[i]) {
        S += abs(pos[i] - j);
        ans.emplace_back(pos[i], j);
        swap(q[j], q[pos[i]]);
        pos[q[j]] = pos[i];
        pos[i] = j;
        // debug(q, pos);
      }
    }
  }
  cout << S << '\n' << (int) ans.size() << '\n';
  for (const auto &[x, y] : ans) {
    cout << x + 1 << ' ' << y + 1 << '\n';
  }
  return 0;
}