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

struct BIT {
  vec<ll> d; int n;
  BIT(int _) : d(_ + 2, 0), n(_) {}
  void add(int p, ll dif) {
    for (; p <= n; p += p & -p) d[p] += dif;
  }
  ll query(int p) {
    ll res = 0;
    for (; p > 0; p &= p - 1) res += d[p];
    return res;
  }
};

void SingleTest(int TestCase) {
  int n; cin >> n;
  int q; cin >> q;
  BIT tr(n);
  for (int op; q--; ) {
    cin >> op;
    if (op == 0) {
      int s, t; ll x;
      cin >> s >> t >> x;
      tr.add(s, x), tr.add(t + 1, -x);
    } else {
      int id; cin >> id;
      cout << tr.query(id) << '\n';
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
