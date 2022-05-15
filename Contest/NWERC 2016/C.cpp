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

void SingleTest(int TestCase) {
  ll x, y; cin >> x >> y;
  int n; cin >> n;
  vec<PII> p(n);
  vec<db>  f(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i].fi >> p[i].se >> f[i];
  }
  auto check = [&](db h) -> bool {
    if (n == 0) return h * y > x;
    db c = p[0].fi + f[0] * (p[0].se - p[0].fi);
    for (int i = 1; i < n; i++) {
      c += (p[i].fi - p[i - 1].se) + f[i] * (p[i].se - p[i].fi);
    }
    c += y - p[n - 1].se;
    return h * c > x;
  };
  db r = 1e8, l = -r;
  for (int _ = 0; _ < 100; _ ++) {
    db m = (l + r) / 2;
    (check(m) ? r : l) = m;
  }
  cout << (l + r) / 2 << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
