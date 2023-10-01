struct ODT {
  map<int, int> mp;
  ODT(int _ = 0, int unit = 0) { mp[_ - 1] = unit; }
  // initialize [_, +infty) with value `unit`
  int get(int x) { return prev(mp.upper_bound(x))->second; }
  void split(int x) { mp[x] = get(x); }
  void assign(int l, int r, int v) {  // assign [l, r), value v
    split(l), split(r);
    auto it = mp.find(l);
    while (it->first != r) it = mp.erase(it);
    mp[l] = v;
  }
};