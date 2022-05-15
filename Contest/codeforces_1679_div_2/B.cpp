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
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

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
  ll lower_bound(ll x) {
    return prev(mp.upper_bound(x))->se;
  }
};

void SingleTest(int TestCase) {
  int n, q; cin >> n >> q;
  ODT tree(1, 0);
  ll sum = 0;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    tree.assign(i, i, x);
    sum += x;
  }
  for (int op; q--; ) {
    cin >> op;
    if (op == 1) {
      int p, v; cin >> p >> v;
      sum += v - tree.lower_bound(p);
      tree.assign(p, p, v);
    } else {
      int v; cin >> v;
      tree = ODT(1, v), sum = (ll) n * v;
    }
    cout << sum << '\n';
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
