struct tree_hash {
  vector<vector<int>> tree;
  vector<ull> H, G;
  // H(u) -> Hash value of subtree(u)
  // G(u) -> Hash value of tree(u-rooted)
  tree_hash(const decltype(tree) &Z) : tree(Z), H(sz(Z), 1), G(sz(Z), 0){};

  void build() {
    const function<void(int, int)> dfs = [&](int u, int fa) {
      for (const int &v : tree[u]) {
        if (v == fa) continue;
        dfs(v, u);
        H[u] += splitmix64(H[v] ^ SEED);
      }
    };
    dfs(0, 0);
    const function<void(int, int)> sol = [&](int u, int fa) {
      for (const int &v : tree[u]) {
        if (v == fa) continue;
        G[v] = H[v] + splitmix64((G[u] - splitmix64(H[v] ^ SEED)) ^ SEED);
        sol(v, u);
      }
    };
    G[0] = H[0];
    sol(0, 0);
  }
};