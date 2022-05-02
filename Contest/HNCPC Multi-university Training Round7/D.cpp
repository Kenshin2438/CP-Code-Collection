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
  int n; cin >> n;
  vec<vec<int>> fac(n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j * j <= i; j++) {
      if (i % j == 0) {
        fac[i].push_back(j);
        if (j * j == i) continue;
        fac[i].push_back(i / j);
      }
    }
  }
  // debug(fac);
  ll s = 0;
  vec<ll> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i], s += a[i];
  }
  ll ans = s;
  for (int _ = 1; _ <= n; _++) {
    ll mi = 1e18; int pos = -1;
    for (int i = 1; i <= n; i++) {
      ll tmp = 0;
      for (int x : fac[i]) {
        tmp += a[x];
      }
      // debug(i, tmp);
      if (tmp < mi) mi = tmp, pos = i;
    }
    // debug(pos, mi);
    // if (mi >= 0) break;
    s -= mi;
    for (int x : fac[pos]) a[x] = 0;
    ans = max(ans, s);
  }
  cout << ans << '\n';
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
