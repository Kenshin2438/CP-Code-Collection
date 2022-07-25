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
  vector<int> col(n);
  for (int &x : col) cin >> x;
  vector<vector<int>> tree(n);
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    --u, --v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  vector<int> dep(n), siz(n), son(n, -1);
  vector<int> dfn(n), seq;
  function<void(int, int)> dfs_son = [&](int u, int fa) {
    dfn[u] = seq.size(), seq.push_back(u);
    siz[u] = 1;
    for (const int &v : tree[u]) {
      if (v == fa) continue;
      dep[v] = dep[u] + 1;
      dfs_son(v, u);
      siz[u] += siz[v];
      if (son[u] == -1 || siz[son[u]] < siz[v]) {
        son[u] = v;
      }
    }
  };
  dfs_son(0, 0);
  vector<ll> ans(n), val(n + 1, 0), cnt(n + 1, 0);
  ll M = 0;
  function<void(int)> add = [&](int x) {
    if (cnt[x] != 0) val[cnt[x]] -= x;
    cnt[x] += 1, val[cnt[x]] += x;
    M = max(M, cnt[x]);
  };
  function<void(int)> del = [&](int x) {
    val[cnt[x]] -= x, cnt[x] -= 1;
    if (cnt[x] != 0) val[cnt[x]] += x;
    while (M > 0 && val[M] == 0) M -= 1;
  };
  function<void(int, int, bool)> dfs = [&](int u, int fa, bool keep) {
    for (const int &v : tree[u]) {
      if (v == fa || v == son[u]) continue;
      dfs(v, u, false);
    }
    if (~son[u]) dfs(son[u], u, true);
    for (const int &v : tree[u]) {
      if (v == fa || v == son[u]) continue;
      for (int i = dfn[v]; i < dfn[v] + siz[v]; i++) {
        add(col[seq[i]]);
      }
    }
    add(col[u]);
    ans[u] = val[M];
    if (keep == false) {
      for (int i = dfn[u]; i < dfn[u] + siz[u]; i++) {
        del(col[seq[i]]);
      }
    }
  };
  dfs(0, 0, false);
  for (const ll &x : ans) cout << x << ' ';
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
