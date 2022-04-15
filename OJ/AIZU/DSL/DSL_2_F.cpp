#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) a.begin(), a.end()

using db = double;
using ll = long long;

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
  ll find(ll l, ll r) {
    split(l), split(r + 1);
    auto it = mp.find(l);
    ll res = (1LL << 31) - 1;
    while (it->fi != r + 1) {
      res = min(res, it->se);
      it = next(it);
    }
    return res;
  }
};

void SingleTest(int TestCase) {
  int n; cin >> n;
  int q; cin >> q;
  ODT tr(0, (1LL << 31) - 1);
  for (int op; q--; ) {
    cin >> op;
    if (op == 0) {
      int s, t; ll x;
      cin >> s >> t >> x;
      tr.assign(s, t, x);
    } else {
      int s, t; cin >> s >> t;
      cout << tr.find(s, t) << '\n';
    }
  }
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
