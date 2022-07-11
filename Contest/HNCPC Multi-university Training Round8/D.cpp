#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

/**
1
4
0 0 1
2 0 1
0 -2 1
2 -2 1
**/

void SingleTest(int TestCase) {
  int n; cin >> n;
  vec<array<ll, 3>> wh(n);
  for (int i = 0; i < n; i++) {
    cin >> wh[i][0] >> wh[i][1] >> wh[i][2];
  }
  vec<vec<int>> tree(n);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      ll dx = wh[i][0] - wh[j][0];
      ll dy = wh[i][1] - wh[j][1];
      ll d  = wh[i][2] + wh[j][2];
      if (dx * dx + dy * dy == d * d) {
        tree[i].push_back(j);
        tree[j].push_back(i);
      }
    }
  }
  vec<array<ll, 3>> ans(n); ans[0] = {1, 1, 1};
  vec<bool> vis(n, false);
  auto dfs = [&](auto self, int u, int fa) -> void {
    if (vis[u]) return;
    vis[u] = true;
    if (~fa) {
      auto [p, q, dir] = ans[fa];
      ll pp = wh[fa][2] * p;
      ll qq = wh[u][2] * q;
      ll g = __gcd(pp, qq);
      if (g) pp /= g, qq /= g;
      else pp = qq = 0;
      ans[u] = {pp, qq, dir ^ 1};
    }
    for (int v : tree[u]) {
      if (v == fa) continue;
      self(self, v, u);
    }
  };
  dfs(dfs, 0, -1);
  for (int i = 0; i < n; i++) {
    auto [p, q, dir] = ans[i];
    if (p == q && p == 0) cout << "not moving\n";
    else {
      if (q == 1) cout << p << ' ';
      else cout << p << '/' << q << ' ';
      cout << (dir ? "clockwise" : "counterclockwise") << '\n';
    }
  }
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
