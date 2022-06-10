#include "../main.hpp"

struct ODT {
  map<ll, ll> mp;

  ODT() = default;
  ODT(ll _, ll unit) { mp[_ - 1] = unit; }
  ~ODT() = default;

  void split(ll x) { mp[x] = prev(mp.upper_bound(x))->second; }
  void assign(ll l, ll r, ll v) {  // assign [l, r), value v
    split(l), split(r);
    auto it = mp.find(l);
    while (it->first != r) it = mp.erase(it);
    mp[l] = v;
  }
  ll query(ll l, ll r) {  // query [l, r)
    split(l), split(r);
    auto it = mp.find(l);
    ll res = 0;
    while (it->first != r) {
      auto nex = next(it);
      res += it->second * (nex->first - it->first);
      it = nex;
    }
    return res;
  }
};
