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
  int m, x, y; cin >> m >> x >> y;
  array<string, 2> s {};
  cin >> s[0] >> s[1];
  s[0].insert(begin(s[0]), '#'), s[0].append("#");
  s[1].insert(begin(s[1]), '#'), s[1].append("#");

  vector<vector<bool>> vis(2, vector<bool>(m + 2, false));
  vector<bool> out(m + 2, false);
  const function<void(int, int, int, int)>
  dfs = [&](int d, int x, int fd, int fx) {
    if (x == 0 || x == m + 1 || vis[d][x]) return;
    vis[d][x] = true;
    if (s[d][x] == 'I') {
      if (d != fd) {
        if (d == 1) return out[x] = true, void();
        else dfs(1, x, 0, x);
      } else {
        dfs(d, x - 1, d, x);
        dfs(d, x + 1, d, x);
      }
    } else {
      if (d != fd) {
        dfs(d, x - 1, d, x);
        dfs(d, x + 1, d, x);
      } else {
        if (d == 1) out[x] = true;
        dfs(0 ^ 1 ^ d, x, d, x);
      }
    }
  };
  if (s[0][x] == 'I') {
    vis[0][x] = true;
    dfs(1, x, 0, x);
  } else {
    vis[0][x] = true;
    if (x - 1 >= 1) dfs(0, x - 1, 0, x);

    vis[0].assign(m + 2, false);
    vis[1].assign(m + 2, false);

    vis[0][x] = true;
    if (x + 1 <= m) dfs(0, x + 1, 0, x);
  }
  cout << (out[y] ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
