#include "../main.hpp"

struct ODT {
  map<int, int> mp;

  ODT() = default;
  ODT(int _, int unit) { mp[_ - 1] = unit; }
  ~ODT() = default;

  void split(int x) { mp[x] = prev(mp.upper_bound(x))->second; }
  int get(int x) { return prev(mp.upper_bound(x))->second; }
  void assign(int l, int r, int v) {  // assign [l, r), value v
    split(l), split(r);
    auto it = mp.find(l);
    while (it->first != r) it = mp.erase(it);
    if (get(l - 1) != v) mp[l] = v;
    if (it->second == v) mp.erase(it);
  }
};
