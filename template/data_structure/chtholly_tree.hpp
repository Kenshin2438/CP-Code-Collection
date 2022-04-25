#include "../main.hpp"

struct ODT {
  map<ll, ll> mp;
  ODT(ll _, ll unit) { mp[_ - 1] = unit; }
  void split(ll x) { mp[x] = prev(mp.upper_bound(x))->se; }
  void assign(ll l, ll r, ll v) {
    split(l), split(r + 1);
    auto it = mp.find(l);
    while (it->fi != r + 1) it = mp.erase(it);
    mp[l] = v;
  }
  ll query(ll l, ll r) {
    split(l), split(r + 1);
    auto it = mp.find(l);
    ll res = 0;
    while (it->fi != r + 1) {
      auto nex = next(it);
      res += it->se * (nex->fi - it->fi);
      it = nex;
    }
    return res;
  }
};
