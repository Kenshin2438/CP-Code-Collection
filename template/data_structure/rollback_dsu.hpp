struct Rollback_DSU {
  vector<int> fa, sz;
  vector<pair<int&, int>> his_fa, his_sz;

  Rollback_DSU() = default;
  Rollback_DSU(int n) : fa(n), sz(n) { init(); }
  ~Rollback_DSU() = default;

  void init() {
    fill(all(sz), 1), iota(all(fa), 0);
    his_sz.clear(), his_fa.clear();
  }
  int find(int x) {
    while (x != fa[x]) x = fa[x];
    return x;
  }
  bool same(int u, int v) {
    return find(u) == find(v);
  }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (sz[u] < sz[v]) swap(u, v);
    his_sz.emplace_back(sz[u], sz[u]);
    his_fa.emplace_back(fa[v], fa[v]);
    sz[u] += sz[v], fa[v] = u;
    return true;
  }
  int history() { return his_fa.size(); }
  void rollback(int h) {
    while ((int) his_fa.size() > h) {
      his_sz.back().first = his_sz.back().second;
      his_fa.back().first = his_fa.back().second;
      his_fa.pop_back(), his_sz.pop_back();
    }
  }
};
