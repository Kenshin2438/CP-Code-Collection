struct Weighted_DSU {
  vector<int> p, val;

  Weighted_DSU() = default;
  Weighted_DSU(int n) : p(n), val(n) { iota(all(p), 0); }
  ~Weighted_DSU() = default;

  int find(int x) {
    if (x == p[x]) return x;
    int fa = find(p[x]);
    val[x] += val[p[x]];
    return p[x] = fa;
  }
  bool same(int x, int y) { return find(x) == find(y); }
  int weight(int x) {
    find(x);
    return val[x];
  }
  int diff(int x, int y) {  // query (a[y] - a[x])
    return weight(y) - weight(x);
  }
  bool merge(int x, int y, int dif = 0) {
    // add constraint (a[y] - a[x] = dif)
    dif = weight(y) - weight(x) - dif;
    x = find(x), y = find(y);
    if (x == y) return false;
    p[x] = y, val[x] = dif;
    return true;
  }
};