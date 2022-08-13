#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int mod = 998244353;
int inv(int x) {
  return x == 1 ? x : (mod - mod / x) * 1LL * inv(mod % x) % mod;
}

void solve() {
  int n, m; cin >> n >> m;
  vector<array<int, 3>> p;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int x; cin >> x;
      p.push_back({x, i, j});
    }
  }
  sort(all(p), greater<>());
  debug(p);
  vector<vector<int>> pos(n, vector<int>(m));
  for (int i = 0; i < (int)p.size(); i++) {
    pos[p[i][1]][p[i][2]] = i;
  }
  ll Sx2 = 0, Sx1 = 0, Sy2 = 0, Sy1 = 0, SoE = 0, SoC = 0;
  ll Tx2 = 0, Tx1 = 0, Ty2 = 0, Ty1 = 0, ToE = 0, ToC = 0;
  vector<int> E((int)p.size(), 0);
  for (int i = p.size() - 1; i >= 0; i--) {
    if (i + 1 != (int)p.size()) {
      if (p[i + 1][0] != p[i][0]) {
        Tx2 = Sx2, Tx1 = Sx1, Ty2 = Sy2, Ty1 = Sy1, ToE = SoE, ToC = SoC;
      }
      if (p[i][0] != p.back()[0]) {
        E[i] = (Tx2 + Ty2 - 2 * p[i][1] * Tx1 % mod - 2 * p[i][2] * Ty1 % mod + ToE + 2 * mod) % mod;
        E[i] = E[i] * 1LL * inv(ToC) % mod;
        E[i] = (E[i] + p[i][1] * 1LL * p[i][1] % mod + p[i][2] * 1LL * p[i][2] % mod) % mod;
      }
    }
    Sx2 = (Sx2 + p[i][1] * 1LL * p[i][1] % mod) % mod;
    Sx1 = (Sx1 + p[i][1] % mod) % mod;
    Sy2 = (Sy2 + p[i][2] * 1LL * p[i][2] % mod) % mod;
    Sy1 = (Sy1 + p[i][2] % mod) % mod;
    SoE = (SoE + E[i]) % mod;
    SoC = (SoC + 1);
  }
  int s, t; cin >> s >> t;
  cout <<  E[pos[s - 1][t - 1]] << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
