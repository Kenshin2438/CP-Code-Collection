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
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

struct ODT {
  map<int, int> mp;
  ODT(int _, int unit) { mp[_ - 1] = unit; }
  void split(int p) {
    mp[p] = prev(mp.upper_bound(p))->se;
  }
  void assign(ll p, ll v) {
    split(p);
    auto it = mp.find(p);
    while (it != end(mp)) {
      if (it->se >= v) it = mp.erase(it);
      else break;
    }
    mp[p] = v;
  }
  int size() { return mp.size() - 1; }
  int query(int p) {
    return prev(mp.upper_bound(p))->se;
  }
};

void SingleTest(__attribute__((unused)) int TestCase) {
  int n, q; cin >> n >> q;

  vec<int> a(n);
  for (int &x : a) cin >> x;

  ODT speed(0, 2e9);
  for (int i = 0; i < n; i++) {
    if (speed.query(i) > a[i]) speed.assign(i, a[i]);
  }

  for (int p, d; q--; ) {
    cin >> p >> d;
    --p;

    a[p] -= d;
    if (speed.query(p) > a[p]) speed.assign(p, a[p]);

    cout << speed.size() << " \n"[q == 0];
  }
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
