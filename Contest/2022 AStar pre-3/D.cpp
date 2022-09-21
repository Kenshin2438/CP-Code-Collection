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

struct DSU {
  vector<int> p, cnt;

  DSU() = default;
  DSU(int n) : p(n, -1), cnt(n, 0) {}
  ~DSU() = default;

  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  int size(int x) { return -p[find(x)]; }
  bool same(int u, int v) { return find(u) == find(v); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) {
      cnt[u] += 1;
      return false;
    }

    p[u] += p[v];
    cnt[u] += cnt[v];
    p[v] = u;
    return true;
  }
};

void solve() {
  int n, m; cin >> n >> m;

  int cntDots = 0;
  vector<string> mat(n);
  for (auto &&s : mat) cin >> s, cntDots += count(all(s), '.');

  DSU dsu(n * m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j + 1 < m; j++) {
      if (mat[i][j] == '#' && mat[i][j + 1] == '#') {
        dsu.merge(i * m + j, i * m + j + 1);
      }
    }
  }
  for (int j = 0; j < m; j++) {
    for (int i = 0; i + 1 < n; i++) {
      if (mat[i][j] == '#' && mat[i + 1][j] == '#') {
        dsu.merge(i * m + j, (i + 1) * m + j);
      }
    }
  }

  vector<ll> ans(3);
  for (int i = 0; i < n * m; i++) {
    if (dsu.find(i) == i && dsu.cnt[i] <= 2) {
      ans[dsu.cnt[i]] += 1;
    }
  }
  cout << (ans[0] - cntDots) << ' ' << ans[1] << ' ' << ans[2] << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
