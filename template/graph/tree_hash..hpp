// https://loj.ac/p/2072
// https://www.luogu.com.cn/problem/P5043
// https://uoj.ac/problem/763

using ull = unsigned long long;

#include <bits/extc++.h>
const int SEED = chrono::steady_clock::now().time_since_epoch().count();
struct chash {  // To use most bits rather than just the lowest ones:
  const ull C = ll(4e18 * acos(0)) | 71;  // large odd number
  ll operator()(ll x) const { return __builtin_bswap64((x ^ SEED) * C); }
};
using HashMap = __gnu_pbds::gp_hash_table<ll, int, chash>;

ull splitmix64(ull x) {
  // http://xorshift.di.unimi.it/splitmix64.c
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}

struct tree_hash {
  int n; // vectex number
  vector<vector<int>> tree;
  vector<ull> H, G;
  // H(u) -> Hash value of subtree(u)
  // G(u) -> Hash value of tree(u-rooted)
  tree_hash(int _n) : n(_n), tree(n), H(n, 1), G(n) {};

  void build() {
    for (int i = 1; i < n; i++) {
      int u, v; cin >> u >> v;
      --u, --v;
      tree[u].emplace_back(v);
      tree[v].emplace_back(u);
    }
    function<void(int, int)> dfs = [&](int u, int fa) {
      for (const int &v : tree[u]) {
        if (v == fa) continue;
        dfs(v, u);
        H[u] += splitmix64(H[v] ^ SEED);
      }
    };
    dfs(0, 0);
    G[0] = H[0];
    function<void(int, int)> sol = [&](int u, int fa) {
      for (const int &v : tree[u]) {
        if (v == fa) continue;
        G[v] = H[v] + splitmix64((G[u] - splitmix64(H[v] ^ SEED)) ^ SEED);
        sol(v, u);
      }
    };
    sol(0, 0);
  }
};
