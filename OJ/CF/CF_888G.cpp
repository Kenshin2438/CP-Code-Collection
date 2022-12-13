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

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (auto &&x : a) cin >> x;

}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
