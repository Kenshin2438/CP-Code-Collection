#include "../data_structure/hash_map.hpp"

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
