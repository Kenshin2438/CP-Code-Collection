#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

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

  string s; cin >> s;
  string t; cin >> t;

  int n = s.length(), m = t.length();
  for (int i = m - 1; i < n; i++) {
    vector<vector<int>> G(26, vector<int>(26));
    for (int j = 0; j < m; j++) {
      int u = s[i - m + 1 + j] - 'a';
      int v = t[j] - 'a';
      G[u][v] = 1;
    }
    DSU dsu(26);
    int ans = 0;
    for (int u = 0; u < 26; u++)
      for (int v = 0; v < 26; v++) 
        if (G[u][v]) ans += dsu.merge(u, v);
    cout << ans << " \n"[i + 1 == n];
  }
  return 0;
}