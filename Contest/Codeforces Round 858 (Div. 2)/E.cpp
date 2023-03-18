#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  int n, q; cin >> n >> q;
  vector<ll> a(n);
  for (ll &x : a) cin >> x;
  vector<vector<int>> tree(n);
  for (int i = 1; i < n; i++) {
    int p; cin >> p; --p;
    tree[p].emplace_back(i);
  }

  vector<int> lg(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
  }
  const int M = 22;
  vector<array<int, M>> p(n, array<int, M> {});
  vector<int> dep(n);

  vector<ll> val(n);
  
  vector<int> L(n), R(n), seq;
  const function<void(int, int)> dfs = [&](int u, int fa) {
    L[u] = sz(seq); seq.emplace_back(u);
    dep[u] = dep[fa] + 1;
    val[u] = val[fa] + a[u] * a[u];
    p[u][0] = fa;
    for (int i = 1; i <= lg[dep[u]]; i++) {
      p[u][i] = p[p[u][i - 1]][i - 1];
    }
    for (const int &v : tree[u]) {
      if (v == fa) continue;
      dfs(v, u);
    }
    R[u] = sz(seq); seq.emplace_back(u);
  };
  dfs(0, 0);

  debug(seq);
  debug(L);
  debug(R);
  debug(dep);
  debug(val);

  const auto lca = [&](int u, int v) -> int {
    if (dep[u] < dep[v]) swap(u, v);
    while (dep[u] > dep[v]) {
      u = p[u][lg[dep[u] - dep[v]] - 1];
    }
    if (u == v) return u;
    for (int i = lg[dep[u]] - 1; i >= 0; i--) {
      if (p[u][i] != p[v][i]) {
        u = p[u][i];
        v = p[v][i];
      }
    }
    return p[u][0];
  };

  vector<ll> ans(q);
  vector<array<int, 3>> Q;
  for (int i = 0; i < q; i++) {
    int x, y; cin >> x >> y; --x, --y;
    int LCA = lca(x, y);
    ans[i] = val[LCA];
    if (x == y) continue;
    
    int l, r;
    if (R[x] < L[y]) {
      l = R[x], r = L[y];
    } else {
      l = R[y], r = L[x];
    }
    assert(l < r);
    ans[i] -= n - (dep[x] - dep[LCA]);
    Q.push_back(array<int, 3>{l, r + 1, i});
  }

  { // Mo's algorithm on tree (euler_tour sequence)
    const int blk = 320;
    sort(all(Q), [&](const auto &A, const auto &B) {
      return pair<int, int>(A[0] / blk, A[1] ^ -(A[0] / blk & 1)) 
           < pair<int, int>(B[0] / blk, B[1] ^ -(B[0] / blk & 1));
    });
    debug(Q);
    vector<int> vis(n, 0);
    vector<ll> D(n + 1, 1); 
    ll S = n;
    const auto f = [&](int x) {
      int nd = seq[x];
      S -= D[dep[nd]];
      if (vis[nd] == 1) {
        D[dep[nd]] /= a[nd];
        vis[nd] = 0;
      } else {
        D[dep[nd]] *= a[nd];
        vis[nd] = 1;
      }
      S += D[dep[nd]];
    };
    const auto calc = [&]() { return S; };

    // assert(false);
    int L = 0, R = 0; // [L, R)
    for (const auto &[l, r, id] : Q) {
      while (L > l) f(--L);
      while (R < r) f(R++);
      while (L < l) f(L++);
      while (R > r) f(--R);
      debug(L, R, l, r);
      debug(S, D);
      ans[id] += calc();
    }
  }

  for (const ll &x : ans) cout << x << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}