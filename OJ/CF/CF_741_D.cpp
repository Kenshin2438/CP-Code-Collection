#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n; cin >> n;
  vector<vector<int>> tree(n);
  vector<int> col(n, 0);
  for (int i = 1; i < n; i++) {
    int x; char c;
    cin >> x >> c;
    tree[x - 1].push_back(i);
    col[i] = 1 << (c - 'a');
  }
  vector<int> dep(n), siz(n), son(n, -1);
  vector<int> dfn(n), seq;
  function<void(int)> dfs_son = [&](int u) {
    dfn[u] = seq.size(), seq.push_back(u);
    siz[u] = 1;
    for (const int &v : tree[u]) {
      dep[v] = dep[u] + 1;
      col[v] ^= col[u];
      dfs_son(v);
      siz[u] += siz[v];
      if (son[u] == -1 || siz[son[u]] < siz[v]) {
        son[u] = v;
      }
    }
  };
  dfs_son(0);
  // debug(dfn, seq);
  vector<int> ans(n), h(1 << 22, -1);
  vector<int> B = { 0 };
  for (char c = 'a'; c <= 'v'; c++) {
    B.push_back(1 << (c - 'a'));
  }
  function<void(int, int)> update = [&](int v, int u) {
    for (const int &x : B) {
      if (~h[col[v] ^ x])
        ans[u] = max(ans[u], h[col[v] ^ x] + dep[v] - 2 * dep[u]);
    }
  };
  function<void(int, bool)> dfs = [&](int u, bool keep) {
    for (const int &v : tree[u]) {
      if (v == son[u]) continue;
      dfs(v, false);
      ans[u] = max(ans[u], ans[v]);
    }
    if (~son[u]) dfs(son[u], true), ans[u] = max(ans[u], ans[son[u]]);
    for (const int &v : tree[u]) {
      if (v == son[u]) continue;
      for (int i = dfn[v]; i < dfn[v] + siz[v]; i++) {
        update(seq[i], u);
      }
      for (int i = dfn[v]; i < dfn[v] + siz[v]; i++) {
        h[col[seq[i]]] = max(h[col[seq[i]]], dep[seq[i]]);
      }
    }
    update(u, u);
    h[col[u]] = max(h[col[u]], dep[u]);
    if (keep == false) {
      for (int i = dfn[u]; i < dfn[u] + siz[u]; i++) {
        h[col[seq[i]]] = -1;
      }
    }
  };
  dfs(0, false);
  for (const int &x : ans) cout << x << ' ';
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
