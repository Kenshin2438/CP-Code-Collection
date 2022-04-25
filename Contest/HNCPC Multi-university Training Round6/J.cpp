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
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

void SingleTest(int TestCase) {
  ll p, k; cin >> p >> k;
  if (k == 0) return cout << "0\n", void();
  if (k >= p) return cout << p - 1 << '\n', void();
  p--; // leq p
  int plus = __builtin_popcountll(p);
  int time = 63 - __builtin_clzll(p);
  if (plus + time <= k) {
    cout << p << '\n';
  } else {
    k--; // x += 1
    ll ans = 1;
    if (k >= time) {
      ans <<= time;
      k -= time;
      for (int w = time - 1; w >= 0 && k > 0; w--) {
        if (p >> w & 1LL) {
          k--, ans |= 1LL << w;
        }
      }
    } else {
      ans <<= k;
    }
    cout << ans << '\n';
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
