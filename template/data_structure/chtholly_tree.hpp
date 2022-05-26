#include "../main.hpp"

struct ODT {
  map<ll, ll> mp;
  ODT(ll _, ll unit) { mp[_ - 1] = unit; }
  void split(ll x) { mp[x] = prev(mp.upper_bound(x))->se; }
  void assign(ll l, ll r, ll v) { // assign [l, r), value v
    split(l), split(r);
    auto it = mp.find(l);
    while (it->fi != r) it = mp.erase(it);
    mp[l] = v;
  }
  ll query(ll l, ll r) { // query [l, r)
    split(l), split(r);
    auto it = mp.find(l);
    ll res = 0;
    while (it->fi != r) {
      auto nex = next(it);
      res += it->se * (nex->fi - it->fi);
      it = nex;
    }
    return res;
  }
};
