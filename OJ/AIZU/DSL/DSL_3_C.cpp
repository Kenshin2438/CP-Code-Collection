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

void SingleTest(int TestCase) {
  int n, q; cin >> n >> q;
  vec<ll> a(n);
  for (auto &x : a) cin >> x;
  for (ll s; q--; ) {
    cin >> s;
    ll ans = 0;
    for (ll S = 0, l = 0, r = 0; r < n; r++) {
      S += a[r];
      while (S > s) S -= a[l++];
      ans += (r - l + 1);
    }
    cout << ans << '\n';
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
