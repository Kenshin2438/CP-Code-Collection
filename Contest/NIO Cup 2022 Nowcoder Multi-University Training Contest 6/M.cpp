#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int N = 505;

int n, m, sb[N][N], vis[N][N];
char s[N][N];

bool dfs(int x, int y) {
  if (x < 1 || x > n || y < 1 || y > m) return false;
  if (vis[x][y]) return true;

  vis[x][y] = true;
  if (s[x][y] != '.') {
    if (s[x][y] == 'A') return sb[x][y] |= (1 << 1), true;
    if (s[x][y] == 'B') return sb[x][y] |= (1 << 2), true;
  }

  #define fi first
  #define se second
  vector<pair<int,int>> t;
  if (dfs(x + 1, y)) t.emplace_back(x + 1, y);
  if (dfs(x, y + 1)) t.emplace_back(x, y + 1);

  int player = (x + y) % 2; // 0 -> Alice; 1 -> Bob
  int sz = t.size();

  if (sz == 0) sb[x][y] |= (1 << 0);
  else if (sz == 1) sb[x][y] = sb[t[0].fi][t[0].se];
  else {
    if (player == 1) {
      sb[x][y] = sb[t[0].fi][t[0].se] & sb[t[1].fi][t[1].se];
    } else {
      sb[x][y] = sb[t[0].fi][t[0].se] | sb[t[1].fi][t[1].se];
    }
  }
  return true;
}

void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> (s[i] + 1);

  if (s[1][1] != '.') {
    if (s[1][1] == 'A') return cout << "yes no no\n", void();
    if (s[1][1] == 'B') return cout << "no no yes\n", void();
  }
  dfs(1, 1);

  cout << ((sb[1][1] & (1 << 1)) ? "yes" : "no") << ' ';
  cout << ((sb[1][1] & (1 << 0)) ? "yes" : "no") << ' ';
  cout << ((sb[1][1] & (1 << 2)) ? "yes" : "no") << '\n';

  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) sb[i][j] = vis[i][j] = 0;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
