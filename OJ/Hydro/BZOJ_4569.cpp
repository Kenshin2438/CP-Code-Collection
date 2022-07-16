#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

struct DSU {
  vector<int> p;

  DSU() = default;
  DSU(int n) : p(n, -1) {}
  ~DSU() = default;

  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  int size(int x) { return -p[find(x)]; }
  bool same(int u, int v) { return find(u) == find(v); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;

    p[u] += p[v], p[v] = u;
    return true;
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n; cin >> n;
  int m; cin >> m;

  vector<DSU> dsu((int) __builtin_log2(n) + 1, DSU(n));

  for (int i = 0; i < m; i++) {
    int l, r; cin >> l >> r;
    int s, t; cin >> s >> t;

    --l, --r, --s, --t;

    int p = (int) __builtin_log2(r - l + 1);
    dsu[p].merge(l, s);
    dsu[p].merge(r - (1 << p) + 1, t - (1 << p) + 1);
  }

  for (int i = dsu.size() - 1; i >= 1; i--) {
    for (int j = 0; j + (1 << i) - 1 < n; j++) {
      int u = j;
      int v = dsu[i].find(j);
      dsu[i - 1].merge(u, v);
      dsu[i - 1].merge(u + (1 << (i - 1)), v + (1 << (i - 1)));
    }
  }

  int cnt = 0;
  for (int i = 0; i < n; i++) {
    cnt += int(dsu[0].find(i) == i);
  }

  const int mod = 1e9 + 7;
  ll ans = 9LL;
  while (--cnt) ans = ans * 10 % mod;
  cout << ans << '\n';
  return 0;
}