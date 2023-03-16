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
  assert(2 <= n && n <= (int) 5e5);
  vector<ll> a(n);
  for (auto && x : a) {
    cin >> x;
    assert(1 <= x && x <= (int) 1e9);
  }

  DSU dsu(n);

  vector<vector<int>> tree(n);
  for (int _ = 0; _ < n - 1; _++) {
    int u, v; cin >> u >> v;
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    --u, --v;
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);

    if (dsu.merge(u, v) == false) {
      assert(false);
    }
  }

  assert(dsu.size(0) == n);

  vector<pair<ll, int>> leaf;
  const function<void(int, int, ll)> dfs = [&](int u, int fa, ll pre) {
    pre += a[u];
    bool is_leaf = true;
    for (const auto &v : tree[u]) {
      if (v == fa) continue;
      dfs(v, u, pre);
      is_leaf = false;
    }
    if (is_leaf) leaf.emplace_back(pre, u);
  };
  dfs(0, 0, 0LL);

  debug(leaf);
  const auto &[M, _] = *max_element(all(leaf));
  
  vector<ll> add(n, 0);
  ll ans = 0;
  for (const auto &[val, idx] : leaf) {
    add[idx] = M - val;
  }

  const function<ll(int, int)> sol = [&](int u, int fa) {
    vector<ll> vals;
    for (const auto &v : tree[u]) {
      if (v == fa) continue;
      vals.emplace_back(sol(v, u));
    }
    if (vals.empty()) return add[u];
    ll res = *min_element(all(vals));
    ans += accumulate(all(vals), 0LL) - res * sz(vals);
    return res;
  };
  ans += sol(0, 0);

  cout << ans << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}