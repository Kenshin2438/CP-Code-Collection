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
  int n; cin >> n;
  ll  t; cin >> t;
  vec<ll> h(n);
  for (ll &x : h) cin >> x;
  cout << t / h[0] + 1 << '\n';
  ll pre = h[0], m = h[0];
  for (int i = 1; i < n; i++) {
    pre += h[i], m = max(m, h[i]);
    if (pre > t) cout << 1 << '\n';
    else cout << (t - pre) / m + 2 << '\n';
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
