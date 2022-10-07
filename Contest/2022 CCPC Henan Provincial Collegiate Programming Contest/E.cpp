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
  int n; cin >> n;
  string s; cin >> s;

  vector<vector<int>> p(26);
  for (int i = 0; i < n; i++) {
    p[s[i] - 'a'].push_back(i);
  }

  for (int i = 0; i < 26; i++) {
    if (sz(p[i]) < 5) continue;
    for (int j = 0; j < 26; j++) {
      if (sz(p[j]) < 7) continue;
      for (int k = 0; k < 26; k++) {
        if (sz(p[k]) < 5) continue;

        int ind = p[i][4] + 1;
        bool ok = true;

        auto it = lower_bound(all(p[j]), ind);
        if (it == end(p[j]) || int(end(p[j]) - it) < 7) ok = false;
        else {
          ind = *(it + 6) + 1;
          auto it = lower_bound(all(p[k]), ind);
          if (it == end(p[k]) || int(end(p[k]) - it) < 5) ok = false;
        }

        if (ok) {
          string ans = "";
          ans.append(5, i + 'a').append(7, j + 'a').append(5, k + 'a');
          return cout << ans << '\n', void();
        }
      }
    }
  }
  cout << "none\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
