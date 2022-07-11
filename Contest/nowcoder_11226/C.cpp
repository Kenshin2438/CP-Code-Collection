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

/**
XOR_i [
  (a_i AND a_1) OR (a_i AND a_2) OR ... OR (a_i AND a_n)
]

1110
1100
0111

cnt: 2321

*/

void SingleTest(int TestCase) {
  int n; cin >> n;
  vec<int> bits(40, 0);
  vec<ll> a(n);
  for (int i = 0; i < n; i++) {
    ll x; cin >> x; a[i] = x;
    for (int j = 32; j >= 0; j--) {
      bits[j] += (x >> j & 1LL);
    }
  }
  debug(bits);
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ll tmp = 0;
    for (int j = 32; j >= 0; j--) {
      ll b = a[i] >> j & 1LL;
      tmp |= b << j;
    }
    ans ^= tmp;
  }
  cout << ans << '\n';
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
