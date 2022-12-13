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
  vector<pair<int, int>> pts(4);
  for (auto &&[x, y] : pts) cin >> x >> y;

  pair<double, double> c;
  c.first = (pts[0].first + pts[2].first) / 2.0;
  c.second = (pts[0].second + pts[2].second) / 2.0;

  vector<array<int, 3>> ls(2);
  for (auto &&[A, B, C] : ls) cin >> A >> B >> C;

  if (ls[0][0] * ls[1][0] + ls[0][1] * ls[1][1] != 0) {
    return cout << "no\n", void();
  }

  pair<double, double> t;
  t.first  = -1.0 * (ls[0][2] * ls[1][1] - ls[1][2] * ls[0][1]) / (ls[0][0] * ls[1][1] - ls[0][1] * ls[1][0]);
  t.second = -1.0 * (ls[0][2] * ls[1][0] - ls[1][2] * ls[0][0]) / (ls[0][1] * ls[1][0] - ls[0][0] * ls[1][1]);

  cout << (t == c ? "yes" : "no") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
